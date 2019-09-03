CC = g++

include_dirs = -I../ -I../GLAD/include -I../include/
debug_symbols = -ggdb

PKGFLAGS = glfw3
CCFLAGS = $(include_dirs) $(debug_symbols)
OBJ = *.o

all: glad.c shader textures
	$(CC)  `pkg-config --cflags $(PKGFLAGS)` $(CCFLAGS) main.cpp glad.c $(OBJ) -o main `pkg-config --static --libs $(PKGFLAGS)` 

shader: shader.cpp
	$(CC) $(CCFLAGS) -c shader.cpp -o shader.o

textures: textures.cpp
	$(CC) $(CCFLAGS) -c textures.cpp -o textures.o
