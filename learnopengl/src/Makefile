CC = g++

include_dirs = -I../ -I../GLAD/include -I../include/
debug_symbols = -ggdb

PKGFLAGS = glfw3
CCFLAGS = $(include_dirs) $(debug_symbols)
OBJ = *.o

all: glad.c shader textures transformations
	$(CC) `pkg-config --cflags $(PKGFLAGS)` $(CCFLAGS) main.cpp glad.c $(OBJ) -o main `pkg-config --static --libs $(PKGFLAGS)` 

cube: shader textures transformations init_gl cube.cpp glad.c
	$(CC) `pkg-config --cflags $(PKGFLAGS)` $(CCFLAGS) cube.cpp glad.c $(OBJ) -o cube `pkg-config --static --libs $(PKGFLAGS)`

shader: shader.cpp
	$(CC) $(CCFLAGS) -c shader.cpp -o shader.o

textures: textures.cpp
	$(CC) $(CCFLAGS) -c textures.cpp -o textures.o

transformations: transformations.cpp
	$(CC) $(CCFLAGS) -c transformations.cpp -o transformations.o

init_gl: init_gl.cpp
	$(CC) $(CCFLAGS) -c init_gl.cpp -o init_gl.o
