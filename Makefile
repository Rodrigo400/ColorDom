CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm

all: game

game: project.cpp 
	g++ $(CFLAGS) project.cpp ppm.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -ogame -D UNIT_TEST -lX11 -lGL -lGLU -lm \
	-D USE_OPENAL_SOUND \
	/usr/lib/x86_64-linux-gnu/libopenal.so \
	/usr/lib/x86_64-linux-gnu/libalut.so
clean:
	rm -f game
	rm -f *.o

