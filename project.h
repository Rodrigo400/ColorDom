// Header File

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

class Game {
    public:
        Shape box;
        Particle particle[MAX_PARTICLES];
        int n;
        Game()
        {
            n = 0;
        }
};

