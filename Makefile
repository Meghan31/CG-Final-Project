CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src -I./src/glad -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lglfw -framework OpenGL

# Core sources - Added Utils.cpp
SRC = src/main.cpp \
      src/Shader.cpp \
      src/glad.c \
      src/utils/Utils.cpp \
      src/rendering/camera/Camera.cpp \
      src/rendering/mesh/Mesh.cpp \
      src/objects/land/Land.cpp \
      src/objects/tree/Tree.cpp \
      src/objects/targets/Target.cpp \
      src/objects/houses/house-1/House1.cpp \
      src/objects/houses/house-2/House2.cpp \
      src/objects/houses/house-3/House3.cpp

OBJ = $(SRC:.cpp=.o)

all: mytown

mytown: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o mytown

clean:
	rm -f mytown *.o src/*.o src/objects/*.o