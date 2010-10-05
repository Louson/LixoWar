PROJECT_NAME = lixo_war
CC = g++
CFLAGS =  -Wall -L/usr/X11R6/lib -lglut -lGLU -lm -lGL -lX11
OBJECTS = Board.o Camera.o Camera_Ortho.o Window.o Camera_Persp.o

all: $(PROJECT_NAME)

$(PROJECT_NAME): main.o $(OBJECTS)
	$(CC) $^ -o $@ $(CFLAGS)

%.o: %.cpp %.h
	$(CC) $< -c -o $@ $(CFLAGS) 

clean:
	rm *.o $(PROJECT_NAME)

