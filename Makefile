PROJECT_NAME = lixo_war
CC = g++
CFLAGS =  -Wall -lm -g
LDFLAGS =  -L/usr/X11R6/lib -lglut -lGLU -lGL -lX11
OBJECTS = main.o Plan.o Texture.o Board.o PlanText.o Sky.o Wall.o Camera.o Camera_Ortho.o Camera_Persp.o\
Located_Light.o\
Spot.o\
Window.o\
File.o\
Config.o\
Moto.o\
Wheel.o\
Game.o\
Color.o\
Beam.o\
Light.o\
Beam.o\
Sound.o\
fmod/lib/libfmodex.so

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.cpp %.h
	$(CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *.o $(PROJECT_NAME)

.PHONY: clean
