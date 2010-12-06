PROJECT_NAME = lixo_war
CC = g++
CFLAGS =  -Wall -lm -g
LDFLAGS =  -L/usr/X11R6/lib -lglut -lGLU -lGL -lX11
OBJECTS = Src/main.o Src/Plan.o Src/Texture.o Src/Board.o Src/PlanText.o Src/Sky.o Src/Wall.o Src/Camera.o Src/Camera_Ortho.o Src/Camera_Persp.o\
Src/Located_Light.o\
Src/Spot.o\
Src/Window.o\
Src/File.o\
Src/Config.o\
Src/Moto.o\
Src/Wheel.o\
Src/Game.o\
Src/Color.o\
Src/Beam.o\
Src/Light.o\
Src/Beam.o\
Src/Sound.o\
lib/libfmodex.so

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CFLAGS)

mrproper: clean
	rm -f $(PROJECT_NAME)

clean:
	rm -f Src/*.o 

run:
	./$(PROJECT_NAME)
.PHONY: clean 
