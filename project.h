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
        struct timespec yellowcharTime, bluecharTime, greencharTime, purplecharTime;
        struct timespec turt1Time, turt2Time, blueportalTime, orangeportalTime;
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
    int boxColorID;
    Shape () {
        width = 25;
        height = 25;
    }
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

extern class Global {
    public:
        int vsync;
        int frameRateOn;
        int xres;
        int yres;
        int done;
        int walk;
        int resultChar1;
        int resultChar2;
        int mainchar1Frame;
        int yellowcharFrame;
        int bluecharFrame;
        int greencharFrame;
        int purplecharFrame;
	    int blueportalFrame;
        int orangeportalFrame;    
        int keys[65536];
        double delay;

        Ppmimage *mainchar1Image;
        Ppmimage *yellowcharImage;
        Ppmimage *bluecharImage;
        Ppmimage *greencharImage;
        Ppmimage *purplecharImage;
        Ppmimage *blueportalImage;
        Ppmimage *orangeportalImage;	

        GLuint mchar1Texture;
        GLuint yellowcharTexture;
        GLuint bluecharTexture;
        GLuint greencharTexture;
        GLuint purplecharTexture;
        GLuint blueportalTexture;
        GLuint orangeportalTexture;

        Vec box[50];
        Global() {
            vsync = 0;
            frameRateOn = 0;
            xres = 1280;
            yres = 720;
            done = 0;
            resultChar1 = 0;
            resultChar2 = 0;
            //
            mainchar1Frame = 0;
            yellowcharFrame = 0;
            bluecharFrame = 0;
            greencharFrame = 0;
            purplecharFrame = 0;
            blueportalFrame = 0;
            orangeportalFrame = 0;
            //
            mainchar1Image = NULL;
            yellowcharImage = NULL;
            bluecharImage = NULL;
            greencharImage = NULL;
            purplecharImage = NULL;
            blueportalImage = NULL;
            orangeportalImage = NULL;

            //
            delay = 0.06;
            /*for (int i = 0; i < 20; i++) {
              box[i][0] = rnd() * xres;
              box[i][1] = rnd() * (yres-220) + 220.0;
              box[i][2] = 0.0;
              }*/
            memset(keys, 0, 65536);
        }
} gl;

class Character {
    public:
        Shape s;
        //Weapon weapon[2];
        float cx;
        float cy;
        float height;
        float width;
        int colorID;
        int points;
        Vec dir;
        Vec pos;
        Vec vel;
        Character () {
            cx = gl.xres/2;
            cy = gl.yres/2;
            height = 45.0;
            width = 45;
            points = 0;
        }
};

class Game {
    public:
        Shape box[125];
        Shape platforms[5];
        Shape boxPerimeter[20];
        Shape backgroundBlock[10];
        Character player[2];
        Particle particle[MAX_PARTICLES];
        int n;
        Game()
        {
            n = 0;
        }
};
#endif
