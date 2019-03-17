OBJS = collisions.cpp interaction.cpp road.cpp tile.cpp vehicle.cpp
CC = g++
# #INCLUDE_PATHS = -I/usr/local/include -I/opt/X11/include
# INCLUDE_PATHS = -I/usr/local/Cellar/glfw/3.2.1/include
# LIBRARY_PATHS = -L/usr/local/Cellar/glfw/3.2.1/lib
#LIBRARY_PATHS = -L/usr/local/lib -I/opt/X11/lib
COMPILER_FLAGS = -w
# LINKER_FLAGS = -framework OpenGL -lglfw -lglew #-lglut
OBJ_NAME = main
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME) -I.
