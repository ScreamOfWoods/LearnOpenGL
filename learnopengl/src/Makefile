CC = g++

include_dirs = -I../ -I../GLAD/include

PKGFLAGS = glfw3
CCFLAGS = $(include_dirs)

all: glad.c
	$(CC)  `pkg-config --cflags $(PKGFLAGS)` $(CCFLAGS) main.cpp glad.c -o main `pkg-config --static --libs $(PKGFLAGS)` 
