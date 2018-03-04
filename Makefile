all: game

game: project.cpp 
	g++ project.cpp libggfonts.a -Wall -ogame -lX11 -lGL -lGLU -lm

clean:
	rm -f game
	rm -f *.o

