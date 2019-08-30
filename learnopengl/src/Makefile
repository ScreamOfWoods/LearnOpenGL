CC = g++

include_dirs = -I../ -I../GLAD/include -I../include/

PKGFLAGS = glfw3
CCFLAGS = $(include_dirs)
OBJ = *.o

all: glad.c shader
	$(CC)  `pkg-config --cflags $(PKGFLAGS)` $(CCFLAGS) main.cpp glad.c $(OBJ) -o main `pkg-config --static --libs $(PKGFLAGS)` 

shader: shader.cpp
	$(CC) $(CCFLAGS) -c shader.cpp -o shader.o
