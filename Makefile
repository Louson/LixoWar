PROJECT_NAME = lixo_war
CC = g++
CFLAGS =  -Wall -L/usr/X11R6/lib -lglut -lGLU -lm -lGL -lX11 -g
LINK= /usr/local/lib/libfmodex32.so

OBJECTS = Plan.o\
Texture.o\
Board.o\
PlanText.o\
Sky.o\
Wall.o\
Camera.o\
Camera_Ortho.o\
Camera_Persp.o\
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
Sound.o

all: $(PROJECT_NAME)

$(PROJECT_NAME): main.o $(OBJECTS)
	$(CC) $^ -o $@ $(CFLAGS) $(LINK)

%.o: %.cpp %.h
	$(CC) $< -c -o $@ $(CFLAGS)

clean:
	rm *.o $(PROJECT_NAME)

