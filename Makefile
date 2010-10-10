PROJECT_NAME = lixo_war
CC = g++
CFLAGS =  -Wall -L/usr/X11R6/lib -lglut -lGLU -lm -lGL -lX11

OBJECTS = Board.o\
Camera.o\
Camera_Ortho.o\
Camera_Persp.o\
Located_Light.o\
Spot.o\
Window.o\
File.o\
Config.o\
Moto.o\
Game.o

all: $(PROJECT_NAME)

$(PROJECT_NAME): main.o $(OBJECTS)
	$(CC) $^ -o $@ $(CFLAGS)

%.o: %.cpp %.h
	$(CC) $< -c -o $@ $(CFLAGS) 

clean:
	rm *.o $(PROJECT_NAME)

