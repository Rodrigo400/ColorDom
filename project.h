#ifndef _GAME_H_
#define _GAME_H_
#include "ppm.h"
// Header File

#include <time.h>
typedef double Flt;
#define rnd() (((double)rand())/(double)RAND_MAX)

// Constants
const int MAX_PARTICLES = 10000;

// Extern Classes
extern class Timers
{
    public:
        double physicsRate;
        double oobillion;
        struct timespec timeStart, timeEnd, timeCurrent;
        struct timespec maincharacterTime;
        struct timespec turt1Time, turt2Time;
        struct timespec gameTime;
        struct timespec timeOut;
        Timers()
        {
            physicsRate = 1.0 / 30.0;
            oobillion = 1.0 / 1e9;
        }
        double timeDiff(struct timespec *start, struct timespec *end)
        {
            return (double)(end->tv_sec - start->tv_sec ) +
                (double)(end->tv_nsec - start->tv_nsec) * oobillion;
        }
        void timeCopy(struct timespec *dest, struct timespec *source)
        {
            memcpy(dest, source, sizeof(struct timespec));
        }
        void recordTime(struct timespec *t)
        {
            clock_gettime(CLOCK_REALTIME, t);
        }
} timers;

//Structures

struct Vec {
    float x, y, z;
};

struct Shape {
    float width, height;
    float radius;
    Vec center;
};

struct Particle {
    Shape s;
    Vec velocity;
};

/*extern class Weapon {
    public:
	Shape s;
	Vec vel;
};*/

extern class Character {
    public:
	Shape s;
	//Weapon weapon[2];
	Vec dir;
	Vec pos;
	Vec vel;
} player1;

extern class Global {
    public:
	int xres;
	int yres;
	int done;
	int walk;
	int result;
	int mcharFrame;
	int keys[65536];
	double delay;

	Ppmimage *mainchar1Image;

	GLuint mchar1Texture;

	Vec box[20];
	Global() {
	    xres = 1280;
	    yres = 720;
	    done = 0;
	    result = 0;
	    //
	    mcharFrame = 0;
	    //
	    mainchar1Image = NULL;

	    //
	    delay = 0.1;
	    /*for (int i = 0; i < 20; i++) {
		box[i][0] = rnd() * xres;
		box[i][1] = rnd() * (yres-220) + 220.0;
		box[i][2] = 0.0;
	    }*/
	    memset(keys, 0, 65536);
	}
} gl;

extern class Game {
    public:
        Shape box[4];
	Shape platforms[5];
	Character player1;
        Particle particle[MAX_PARTICLES];
        int n;
        Game()
        {
            n = 0;
        }
} game;
#endif
