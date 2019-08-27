CC = g++

include_dirs = -I../ -I../GLAD/include

PKGFLAGS = glfw3
CCFLAGS = $(include_dirs)

all:
	$(CC)  `pkg-config --cflags $(PKGFLAGS)` $(CCFLAGS) main.cpp -o main `pkg-config --static --libs $(PKGFLAGS)` 
