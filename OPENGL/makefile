INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/X11R6/lib 

COMPILERFLAGS = -Wall
CC = gcc
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm 

all:  lesson1 lesson2 lesson3 lesson4 lesson5 lesson6 lesson7

lesson1 : lesson1.o
	$(CC) $(CFLAGS) -o lesson1 $(LIBDIR) lesson1.o $(LIBRARIES)  

lesson2 : lesson2.o
	$(CC) $(CFLAGS) -o lesson2 $(LIBDIR) lesson2.o $(LIBRARIES)  

lesson3 : lesson3.o
	$(CC) $(CFLAGS) -o lesson3 $(LIBDIR) lesson3.o $(LIBRARIES)  

lesson4 : lesson4.o
	$(CC) $(CFLAGS) -o lesson4 $(LIBDIR) lesson4.o $(LIBRARIES)  

lesson5 : lesson5.o
	$(CC) $(CFLAGS) -o lesson5 $(LIBDIR) lesson5.o $(LIBRARIES)  

lesson6 : lesson6.o
	$(CC) $(CFLAGS) -o lesson6 $(LIBDIR) lesson6.o $(LIBRARIES)  

lesson7 : lesson7.o
	$(CC) $(CFLAGS) -o lesson7 $(LIBDIR) lesson7.o $(LIBRARIES)  

