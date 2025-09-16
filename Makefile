CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src -I./src/glad -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lglfw -framework OpenGL

# Core sources - Added Utils.cpp
SRC = src/main.cpp \
      src/Camera.cpp \
      src/Shader.cpp \
      src/Mesh.cpp \
      src/Utils.cpp \
      src/glad.c \
      src/objects/Land.cpp \
      src/objects/House.cpp \
      src/objects/Tree.cpp \
      src/objects/Target.cpp

OBJ = $(SRC:.cpp=.o)

all: mytown

mytown: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o mytown

clean:
	rm -f mytown *.o src/*.o src/objects/*.o