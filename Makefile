###############################################################################
# Cross-platform Makefile for GLFW + GLAD + OpenGL (macOS/Linux/Windows MSYS)
# - Uses pkg-config when available for glfw3 and glm
# - Adds Homebrew fallbacks on macOS
# - Provides reasonable defaults on Linux and Windows/MSYS-MinGW
###############################################################################

# Executable name
EXE ?= hw4

# Compilers (override from environment if desired)
CC  ?= cc
CXX ?= c++

# Language standards
CSTD   ?= c11
CPPSTD ?= c++17

# Base warnings and include paths for project sources
CFLAGS   += -std=$(CSTD) -Wall -Wextra -I./src -I./src/glad
CXXFLAGS += -std=$(CPPSTD) -Wall -Wextra -I./src -I./src/glad

# Try to use pkg-config for glfw3 and glm (header-only) if available
PKG_CFLAGS := $(shell pkg-config --cflags glfw3 glm 2>/dev/null)
PKG_LIBS   := $(shell pkg-config --libs glfw3 2>/dev/null)
CFLAGS     += $(PKG_CFLAGS)
CXXFLAGS   += $(PKG_CFLAGS)
LDFLAGS    += $(PKG_LIBS)

# Detect platform
ifeq ($(OS),Windows_NT)
    PLATFORM := Windows
else
    UNAME_S := $(shell uname)
    ifeq ($(UNAME_S),Darwin)
        PLATFORM := Mac
    else
        PLATFORM := Linux
    endif
endif

# Platform-specific flags and fallbacks
ifeq ($(PLATFORM),Mac)
    # Homebrew fallback for includes/libs if pkg-config wasn't used
    BREW_PREFIX := $(shell brew --prefix 2>/dev/null)
    ifneq ($(BREW_PREFIX),)
        CFLAGS   += -I$(BREW_PREFIX)/include
        CXXFLAGS += -I$(BREW_PREFIX)/include
        LDFLAGS  += -L$(BREW_PREFIX)/lib
    endif
    # If pkg-config didn't supply glfw libs, link explicitly
    ifeq ($(strip $(PKG_LIBS)),)
        LDFLAGS += -lglfw
    endif
    # OpenGL framework on macOS
    LDFLAGS += -framework OpenGL
endif

ifeq ($(PLATFORM),Linux)
    # If pkg-config didn't supply glfw libs, add common Linux deps
    ifeq ($(strip $(PKG_LIBS)),)
        LDFLAGS += -lglfw -lGL -ldl -lpthread -lX11 -lXrandr -lXi
    endif
endif

ifeq ($(PLATFORM),Windows)
    # Prefer pkg-config under MSYS2 if present; else fallback minimal set
    ifeq ($(strip $(PKG_LIBS)),)
        LDFLAGS += -lglfw3 -lopengl32 -lgdi32 -lwinmm
    endif
endif

# Core sources - Separate C and C++ files
SRC_CPP = src/main.cpp \
                    src/Shader.cpp \
                    src/utils/Utils.cpp \
                    src/rendering/camera/Camera.cpp \
                    src/rendering/mesh/Mesh.cpp \
                    src/objects/land/Land.cpp \
                    src/objects/tree/Tree.cpp \
                    src/objects/targets/Target.cpp \
                    src/objects/houses/house-1/House1.cpp \
                    src/objects/houses/house-2/House2.cpp \
                    src/objects/houses/house-3/House3.cpp

SRC_C = src/glad.c

OBJ_CPP = $(SRC_CPP:.cpp=.o)
OBJ_C   = $(SRC_C:.c=.o)

all: $(EXE)

$(EXE): $(OBJ_CPP) $(OBJ_C)
	$(CXX) $(OBJ_CPP) $(OBJ_C) -o $@ $(LDFLAGS)

# Compile C++ files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXE) $(OBJ_CPP) $(OBJ_C)