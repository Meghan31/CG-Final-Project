CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src -I./src/glad -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lglfw -framework OpenGL

SRC = src/main.cpp src/Camera.cpp src/Shader.cpp src/Mesh.cpp src/Objects.cpp src/glad.c
OBJ = $(SRC:.cpp=.o)

all: mytown

mytown: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o mytown

clean:
	rm -f mytown *.o src/*.o
	