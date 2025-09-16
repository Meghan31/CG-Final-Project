CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src -I./src/glad -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lglfw -framework OpenGL

# Core sources - Added Utils.cpp
# FIXED: Separate C and C++ files
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

# Separate C file
SRC_C = src/glad.c

OBJ_CPP = $(SRC_CPP:.cpp=.o)
OBJ_C = $(SRC_C:.c=.o)

all: mytown

mytown: $(OBJ_CPP) $(OBJ_C)
	$(CXX) $(OBJ_CPP) $(OBJ_C) $(LDFLAGS) -o mytown

# Compile C++ files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C files with gcc
%.o: %.c
	gcc -I./src -I./src/glad -I/opt/homebrew/include -c $< -o $@

clean:
	rm -f mytown $(OBJ_CPP) $(OBJ_C)