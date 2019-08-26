CC = g++

include_dirs = -I../
lib_dirs = -L../GLFW/lib

LINKERFLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
CCFLAGS = $(include_dirs) $(lib_dirs) $(LINKERFLAGS)

all:
	$(CC) $(CCFLAGS) main.cpp -o main 

