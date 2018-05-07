
//===============================================
// Created By:
//      Rodrigo Garcia-Novoa
//
// Frameworks By:
//      Gordon Griesel
//===============================================


//#include "context_gl_x11.h"
#include <GL/glx.h>
#include <GL/glxext.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctime>
#include <sys/time.h>
#include <cstring>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include <fcntl.h>
#include <sys/stat.h>
#ifdef USE_OPENAL_SOUND  
#include </usr/include/AL/alut.h>
#endif //USE_OPENAL_SOUND

#include "ppm.h"
#include "fonts.h"
#include "project.h"                    // header file
using namespace std;

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 720
#define GRAVITY 0.1

class Sound {
    public:
        ALuint alBufferTitle;
        ALuint alBufferScroll;
        ALuint alBufferSelect;
        ALuint alBufferApplause;
        ALuint alBufferGame;
        ALuint alBufferThree;
        ALuint alBufferTwo;
        ALuint alBufferOne;
        ALuint alBufferGo;
        ALuint alBufferDrums;
        ALuint alBufferBell;

        ALuint alSourceTitle;
        ALuint alSourceScroll;
        ALuint alSourceSelect;
        ALuint alSourceApplause;
        ALuint alSourceGame;
	ALuint alSourceThree;
	ALuint alSourceTwo;
	ALuint alSourceOne;
	ALuint alSourceGo;
	ALuint alSourceDrums;
	ALuint alSourceBell;
};


//===============================================
// SOUND
// ==============================================
void initialize_sound() 
{
    alutInit(0, NULL);

    float vec[6] = {0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f};
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListenerfv(AL_ORIENTATION, vec);
    alListenerf(AL_GAIN, 1.0f);

    /*s.alBufferTitle = alutCreateBufferFromFile("./sound/GameMusic.wav");

    alGenSources(1, &s.alSourceTitle);
    alSourcei(s.alSource, AL_BUFFER, s.alBufferTitle);

    alSourcef(s.alSourceTitle, AL_GAIN, 1.0f);
    alSourcef(s.alSourceTitle, AL_PITCH, 1.0f);
    alSourcei(s.alSourceTitle, AL_LOOPING, AL_TRUE);*/
}

void playMusicTitle() 
{
    Sound s;

    s.alBufferTitle = alutCreateBufferFromFile("./sound/TitleMusic.wav");

    alGenSources(1, &s.alSourceTitle);
    alSourcei(s.alSourceTitle, AL_BUFFER, s.alBufferTitle);

    alSourcef(s.alSourceTitle, AL_GAIN, 1.0f);
    alSourcef(s.alSourceTitle, AL_PITCH, 1.0f);
    alSourcei(s.alSourceTitle, AL_LOOPING, AL_TRUE);
    
    alSourcePlay(s.alSourceTitle);
}

void playMusicGame() 
{
    Sound s;

    s.alBufferGame = alutCreateBufferFromFile("./sound/GameMusic.wav");

    alGenSources(1, &s.alSourceGame);
    alSourcei(s.alSourceGame, AL_BUFFER, s.alBufferGame);

    alSourcef(s.alSourceGame, AL_GAIN, 0.35f);
    alSourcef(s.alSourceGame, AL_PITCH, 1.0f);
    alSourcei(s.alSourceGame, AL_LOOPING, AL_TRUE);
    
    alSourcePlay(s.alSourceGame);
}

void playScroll() 
{
    Sound s;

    s.alBufferScroll = alutCreateBufferFromFile("./sound/scrollSound.wav");

    alGenSources(1, &s.alSourceScroll);
    alSourcei(s.alSourceScroll, AL_BUFFER, s.alBufferScroll);

    alSourcef(s.alSourceScroll, AL_GAIN, 1.0f);
    alSourcef(s.alSourceScroll, AL_PITCH, 1.0f);
    alSourcei(s.alSourceScroll, AL_LOOPING, AL_FALSE);

    alSourcePlay(s.alSourceScroll);
}

void playSelect() 
{
    Sound s;

    s.alBufferSelect = alutCreateBufferFromFile("./sound/selectSound.wav");

    alGenSources(1, &s.alSourceSelect);
    alSourcei(s.alSourceSelect, AL_BUFFER, s.alBufferSelect);

    alSourcef(s.alSourceSelect, AL_GAIN, 1.0f);
    alSourcef(s.alSourceSelect, AL_PITCH, 1.0f);
    alSourcei(s.alSourceSelect, AL_LOOPING, AL_FALSE);
    
    alSourcePlay(s.alSourceSelect);
}

void playApplause() 
{
    Sound s;

    s.alBufferApplause = alutCreateBufferFromFile("./sound/applauseSound.wav");

    alGenSources(1, &s.alSourceApplause);
    alSourcei(s.alSourceApplause, AL_BUFFER, s.alBufferApplause);

    alSourcef(s.alSourceApplause, AL_GAIN, 1.0f);
    alSourcef(s.alSourceApplause, AL_PITCH, 1.0f);
    alSourcei(s.alSourceApplause, AL_LOOPING, AL_FALSE);
    
    alSourcePlay(s.alSourceApplause);
}

void playThree() 
{
    Sound s;

    s.alBufferThree = alutCreateBufferFromFile("./sound/three.wav");

    alGenSources(1, &s.alSourceThree);
    alSourcei(s.alSourceThree, AL_BUFFER, s.alBufferThree);

    alSourcef(s.alSourceThree, AL_GAIN, 1.0f);
    alSourcef(s.alSourceThree, AL_PITCH, 1.0f);
    alSourcei(s.alSourceThree, AL_LOOPING, AL_FALSE);
    
    alSourcePlay(s.alSourceThree);
}

void playTwo() 
{
    Sound s;

    s.alBufferTwo = alutCreateBufferFromFile("./sound/two.wav");

    alGenSources(1, &s.alSourceTwo);
    alSourcei(s.alSourceTwo, AL_BUFFER, s.alBufferTwo);

    alSourcef(s.alSourceTwo, AL_GAIN, 1.0f);
    alSourcef(s.alSourceTwo, AL_PITCH, 1.0f);
    alSourcei(s.alSourceTwo, AL_LOOPING, AL_FALSE);
    
    alSourcePlay(s.alSourceTwo);
}

void playOne() 
{
    Sound s;

    s.alBufferOne = alutCreateBufferFromFile("./sound/one.wav");

    alGenSources(1, &s.alSourceOne);
    alSourcei(s.alSourceOne, AL_BUFFER, s.alBufferOne);

    alSourcef(s.alSourceOne, AL_GAIN, 1.0f);
    alSourcef(s.alSourceOne, AL_PITCH, 1.0f);
    alSourcei(s.alSourceOne, AL_LOOPING, AL_FALSE);
    
    alSourcePlay(s.alSourceOne);
}

void playGo() 
{
    Sound s;

    s.alBufferGo = alutCreateBufferFromFile("./sound/go.wav");

    alGenSources(1, &s.alSourceGo);
    alSourcei(s.alSourceGo, AL_BUFFER, s.alBufferGo);

    alSourcef(s.alSourceGo, AL_GAIN, 1.0f);
    alSourcef(s.alSourceGo, AL_PITCH, 1.0f);
    alSourcei(s.alSourceGo, AL_LOOPING, AL_FALSE);
    
    alSourcePlay(s.alSourceGo);
}

void playDrums() 
{
    Sound s;

    s.alBufferDrums = alutCreateBufferFromFile("./sound/drum.wav");

    alGenSources(1, &s.alSourceDrums);
    alSourcei(s.alSourceDrums, AL_BUFFER, s.alBufferDrums);

    alSourcef(s.alSourceDrums, AL_GAIN, 1.0f);
    alSourcef(s.alSourceDrums, AL_PITCH, 1.0f);
    alSourcei(s.alSourceDrums, AL_LOOPING, AL_FALSE);
    
    alSourcePlay(s.alSourceDrums);
}

void playBell() 
{
    Sound s;

    s.alBufferBell = alutCreateBufferFromFile("./sound/bell.wav");

    alGenSources(1, &s.alSourceBell);
    alSourcei(s.alSourceBell, AL_BUFFER, s.alBufferBell);

    alSourcef(s.alSourceBell, AL_GAIN, 1.0f);
    alSourcef(s.alSourceBell, AL_PITCH, 1.0f);
    alSourcei(s.alSourceBell, AL_LOOPING, AL_FALSE);
    
    alSourcePlay(s.alSourceBell);
}

void finish_sound() 
{
    Sound s;
    alDeleteSources(1, &s.alSourceTitle);
    alDeleteSources(1, &s.alSourceScroll);
    alDeleteSources(1, &s.alSourceSelect);
    alDeleteSources(1, &s.alSourceApplause);
    alDeleteSources(1, &s.alSourceGame);
    alDeleteSources(1, &s.alSourceThree);
    alDeleteSources(1, &s.alSourceTwo);
    alDeleteSources(1, &s.alSourceOne);
    alDeleteSources(1, &s.alSourceGo);
    alDeleteSources(1, &s.alSourceDrums);

    alDeleteBuffers(1, &s.alBufferTitle);
    alDeleteBuffers(1, &s.alBufferScroll);
    alDeleteBuffers(1, &s.alBufferSelect);
    alDeleteBuffers(1, &s.alBufferApplause);
    alDeleteBuffers(1, &s.alBufferGame);
    alDeleteBuffers(1, &s.alBufferThree);
    alDeleteBuffers(1, &s.alBufferTwo);
    alDeleteBuffers(1, &s.alBufferOne);
    alDeleteBuffers(1, &s.alBufferGo);
    alDeleteBuffers(1, &s.alBufferDrums);

    ALCcontext *Context = alcGetCurrentContext();
    ALCdevice *Device = alcGetContextsDevice(Context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(Context);
    alcCloseDevice(Device);

    alutExit();
}
//===============================================
// SOUND END
// ==============================================


//defined types
//typedef double Vec[3];
typedef double Flt;
typedef Flt Matrix[4][4];

//macros
#define rnd() (((double)rand())/(double)RAND_MAX)
#define random(a) (rand()%a)
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b) ((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
			     (c)[1]=(a)[1]-(b)[1]; \
(c)[2]=(a)[2]-(b)[2]
//constants
const float timeslice = 1.0f;
const float gravity = -9;
//const int MAX_PARTICLES = 10000;
#define ALPHA 1


//===============================================
// Global Instance
// ==============================================
Timers timers;
Global gl;
Character *char1, *char2;
Shape *globalSaveBox;
Game game;
//Shape *s;
//bool leftFaceChar1 = 0; 
//bool leftFaceChar2 = 0; 
int colorChangeFlag = 0;
bool gravityOn = true;
bool char1inAirBool = true;
bool char2inAirBool = true;
bool moveUpBool = true;
bool moveDownBool = true;
bool moveRightBool = true;
bool moveLeftBool = true;
bool initializeFlag = 1;
bool pointFlag = 0;
bool one = true;
bool two = true;
bool three = true;
bool go = true;
bool musicGameFlag = 0;
bool musicTitleFlag = 1;
float finalJumpCy;
float jumpStartCy;
int boxIndex;
int gameFrame = 30;
//int gameFrame = 5;
int timeoutFrame = 0;
int gameDelay = 1;
int totalCubes;
int bellFlag = 1;
int appFlag = 1;	
int drumsFlag = 1;	

int xres3, xres4;
unsigned char *screendata = NULL;
//s = &game->box[i];
//Sprite
//
//Particle
//
//game
// ==============================================
//X Windows variables
Display *dpy;
Window win;
GLXContext glc;
// ==============================================

//Function prototypes
void showFrameRate();
void setup_screen_res(const int w, const int h);
void initXWindows(int w, int h);
//int main(void);
void init_opengl(void);
void cleanupXWindows(void);
void check_resize(XEvent *e);
void check_mouse(XEvent *e);
void check_keys(XEvent *e);
void physics(Game *game);
void render(Game *game);
void rWithoutAlpha(GLuint, int, int);
void rWithAlpha(int, int, int, int, GLuint);
void renderFrame(int, int, int, int, GLuint);
void sCharPose(int, int, int, int, GLuint, int, int);
void physicsPortal();
void heartCollision(Character *);
// ==============================================
// Functions
// ==============================================
void jump(Character *);
void checkJump();
void changeColor(Character*, Shape*);
void awardPoint(Character*, Shape*);
void removePoint(Character*, Character*, Shape*);
void countdown3(int, int);
void countdown2(int, int);
void countdown1(int, int);
void countdowngo(int, int);
void startCountdown();
bool checkCountdown();
void resetEverything();
//void playerCollision(Character*);

// UI FUNCTIONS
void drawTimerBackground(); 
void drawCircleUI1(); 
void drawCircleUI2();
void drawHealthBar1(); 
void drawHealthBar2(); 
void drawBluePortal();
void drawOrangePortal();
void drawProfile1(GLuint); 
void drawProfile2(GLuint);
void drawHealthVal1();
void drawHealthVal2();
void drawPlayerOne(GLuint);
void drawPlayerTwo(GLuint);
void drawFrameRate();
void drawStartMenu();
void drawControlsMenu();
void drawCharSelectMenu();
void drawCredits();
void drawWinner();
void drawBullet(Character *, GLuint);
// ==============================================


// ==============================================
const double oothousand = 1.0 / 1000.0;
struct timeval gamestarttv;
int xxGetTicks() {
    struct timeval end;
    gettimeofday(&end, NULL);
    //long seconds  = end.tv_sec  - gamestarttv.tv_sec;
    //long useconds = end.tv_usec - gamestarttv.tv_usec;
    //long mtime = (seconds*1000 + useconds*oothousand) + 0.5;
    //return (int)mtime;
    //code above compressed...
    return (int)((end.tv_sec - gamestarttv.tv_sec) * 1000 +
	    (end.tv_usec - gamestarttv.tv_usec) * oothousand) + 0.5;
}

int main(int argc, char *argv[])
{
    alutInit(0, NULL);
    srand(time(NULL));
    //initXWindows();
    //init_opengl();

    //declare game object
    //Game game;
    char1 = &game.player[0];
    char2 = &game.player[1];
    char1->cx = 210;
    char2->cx = 1080;
    char1->cy = gl.yres/2 + 15;
    char2->cy = gl.yres/2 + 15;

    //declare a box shape
    //game.box[0].width = 300;
    //game.box[0].height = 50;
    //game.box[0].center.x = gl.xres/2;
    //game.box[0].center.y = 450;

    // bottom boxes row
    for (int i = 1; i < 22; i++) {
	game.box[i].width = 25;
	game.box[i].height = 25;
	game.box[i].center.x = 55*i + 35;
	game.box[i].center.y = 155;
	if (i == 11) {
	    game.box[i].center.x = 55*i + 35;
	    game.box[i].center.y = 155+60;
	}
    }
    int total = 1;
    // top row
    for (int i = 22; i < 43; i++) {
	game.box[i].width = 25;
	game.box[i].height = 25;
	game.box[i].center.x = 55*total + 35;
	game.box[i].center.y = gl.yres-65;
	total++;
    }
    total = 1;
    // left side
    for (int i = 43; i < 51; i++) {
	game.box[i].width = 25;
	game.box[i].height = 25;
	game.box[i].center.x = 37;
	game.box[i].center.y = 55*total+155;
	if (i == 46 || i == 47) {
	    game.box[i].center.x = -3700;
	    game.box[i].center.y = 55*total+155;
	}
	total++;
    }
    total = 1;
    // right side
    for (int i = 51; i < 59; i++) {
	game.box[i].width = 25;
	game.box[i].height = 25;
	game.box[i].center.x = gl.xres-37;
	game.box[i].center.y = 55*total+155;
	if (i == 54 || i == 55) {
	    game.box[i].center.x = -3700;
	    game.box[i].center.y = 55*total+155;
	}
	total++;
    }
    //
    // Bottom half
    //
    // left platform
    total = 1;
    for (int i = 59; i < 63; i++) {
	game.box[i].width = 25;
	game.box[i].height = 25;
	game.box[i].center.x = 55*total + 150;
	game.box[i].center.y = 300;
	total++;
    }
    // right platform
    total = 1;
    for (int i = 63; i < 67; i++) {
	game.box[i].width = 25;
	game.box[i].height = 25;
	game.box[i].center.x = 55*total + 860;
	game.box[i].center.y = 300;
	total++;
    }
    // middle pyramid
    total = 1;
    for (int i = 67; i < 70; i++) {
	game.box[i].width = 25;
	game.box[i].height = 25;
	if (i == 68) {
	    game.box[i].center.x = 55*total + 530;
	    game.box[i].center.y = 355;
	} else {
	    game.box[i].center.x = 55*total + 530;
	    game.box[i].center.y = 300;
	}
	total++;
    }
    //
    // Top Half
    // 55 wide height
    // left side
    total = 1;
    for (int i = 70; i < 75; i++) {
	game.box[i].width = 25;
	game.box[i].height = 25;
	if (i == 74) {
	    game.box[i].center.x = 55*total + 205;
	    game.box[i].center.y = 435;
	} else if (i == 70) {
	    game.box[i].center.x = 55*total + 205;
	    game.box[i].center.y = 435;
	} else {
	    game.box[i].center.x = 55*total + 205;
	    game.box[i].center.y = 486;
	}
	total++;
    }
    // right side
    total = 1;
    for (int i = 75; i < 80; i++) {
	game.box[i].width = 25;
	game.box[i].height = 25;
	if (i == 75) {
	    game.box[i].center.x = 55*total + 750;
	    game.box[i].center.y = 435;
	} else if (i == 79) {
	    game.box[i].center.x = 55*total + 750;
	    game.box[i].center.y = 435;
	} else {
	    game.box[i].center.x = 55*total + 750;
	    game.box[i].center.y = 486;
	}
	total++;
    }
    totalCubes = 80;


    int x=0, y=0; 
    if (argc > 2) {
	x = atoi(argv[1]);
	y = atoi(argv[2]);
    }
    //if (argc > 3)
    //showOpengl = 1;

    initXWindows(x, y);
    setup_screen_res(gl.xres, gl.yres);
    init_opengl();
    //int done = 0;
    gettimeofday(&gamestarttv, NULL);

    //===================================
    // MUSIC HERE
    //===================================
    initialize_sound();
    playMusicGame();
    //===================================

    while (!gl.done) {
	while (XPending(dpy)) {
	    XEvent e;
	    XNextEvent(dpy, &e);
	    check_resize(&e);
	    check_mouse(&e);
	    check_keys(&e);
	}
	//printf("Title flag: %d\n", musicTitleFlag);
	//printf("Game flag: %d\n", musicGameFlag);
	if (gameFrame > 0 && !go) 
	    physics(&game);

	/*if (musicTitleFlag && !musicGameFlag) {
	    playMusicTitle();
	    musicTitleFlag = 0;
	}
	if (musicGameFlag && !musicTitleFlag) {
	    playMusicGame();
	    musicGameFlag = 0;
	}*/

	render(&game);
	glXSwapBuffers(dpy, win);
	showFrameRate();
    }
    cleanupXWindows();
    finish_sound();
    return 0;
}

void set_title(void)
{
    //Set the window title bar.
    XMapWindow(dpy, win);
    XStoreName(dpy, win, "\t\t\t\t\t Color Domination");
}

void cleanupXWindows(void)
{
    //do not change
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
}

float fps;

void showFrameRate()
{
    static int count=0;
    static int lastt = xxGetTicks();
    if (++count >= 32) {
	int diff = xxGetTicks() - lastt;
	//32 frames took diff 1/1000 seconds.
	//how much did 1 frame take?
	float secs = (float)diff / 1000.0;
	//frames per second...
	fps = (float)count / secs;
	//printf("frame rate: %f\n", fps);
	count = 0;
	lastt = xxGetTicks();
    }
}

#ifdef UNIT_TEST
void setup_screen_res(const int w, const int h)
{
    gl.xres = w;
    gl.yres = h;
    xres3 = gl.xres * 3;
    xres4 = gl.xres * 4;
    if (screendata)
	delete [] screendata;
    screendata = new unsigned char[gl.yres * xres4];


    if (gl.xres != 1280 || gl.yres != 720) 
	printf("Unit test failed. Not 1280x720\n");
    else 
	printf("Unit test passed.\n");
}
#endif //UNIT_TEST

void initXWindows(int w, int h)
{
    //do not change
    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    //int w=WINDOW_WIDTH, h=WINDOW_HEIGHT;
    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
	std::cout << "\n\tcannot connect to X server\n" << std::endl;
	exit(EXIT_FAILURE);
    }
    Window root = DefaultRootWindow(dpy);
    // for fullscreen
    XWindowAttributes getWinAttr;
    XGetWindowAttributes(dpy, root, &getWinAttr);
    int fullscreen = 0;
    gl.xres = w;
    gl.yres = h;
    if (!w && !h) {
	//Go to fullscreen.
	gl.xres = getWinAttr.width;
	gl.yres = getWinAttr.height;
	printf("getWinAttr: %i %i\n", w, h); fflush(stdout);
	//When window is fullscreen, there is no client window
	//so keystrokes are linked to the root window.
	XGrabKeyboard(dpy, root, False,
		GrabModeAsync, GrabModeAsync, CurrentTime);
	fullscreen = 1;
    }

    XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
    if (vi == NULL) {
	std::cout << "\n\tno appropriate visual found\n" << std::endl;
	exit(EXIT_FAILURE);
    } 
    Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
    XSetWindowAttributes swa;
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
	ButtonPress | ButtonReleaseMask | PointerMotionMask |
	StructureNotifyMask | SubstructureNotifyMask;

    unsigned int winops = CWBorderPixel|CWColormap|CWEventMask;
    if (fullscreen) {
	winops |= CWOverrideRedirect;
	swa.override_redirect = True;
    }
    printf("2 getWinAttr: %i %i\n", w, h); fflush(stdout);

    //win = XCreateWindow(dpy, root, 0, 0, gl.xres, gl.yres, 0, vi->depth,
    //    InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
    win = XCreateWindow(dpy, root, 0, 0, gl.xres, gl.yres, 0,
	    vi->depth, InputOutput, vi->visual, winops, &swa);


    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);
    set_title();
}

void renderViewport(const int y, const int w, const int h)
{
    //x: column, is always 0
    //y: row
    //w: width of area to be drawn
    //h: height of area to be drawn
    unsigned char *p = screendata + (y * xres4);
    //Log("render_viewport(%i %i %i %i)\n", 0, y, w, h);
    glRasterPos2i(0, y);
    glDrawPixels(w, h, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid *)p);
}

void reshape_window(int width, int height)
{
    //window has been resized.
    setup_screen_res(width, height);
    //
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
    set_title();
}


unsigned char *buildAlphaData(Ppmimage *img)
{
    //add 4th component to RGB stream...
    int i;
    unsigned char *newdata, *ptr;
    unsigned char *data = (unsigned char *)img->data;
    newdata = (unsigned char *)malloc(img->width * img->height * 4);
    ptr = newdata;
    unsigned char a,b,c;
    //use the first pixel in the image as the transparent color.
    unsigned char t0 = *(data+0);
    unsigned char t1 = *(data+1);
    unsigned char t2 = *(data+2);
    for (i=0; i<img->width * img->height * 3; i+=3) {
	a = *(data+0);
	b = *(data+1);
	c = *(data+2);
	*(ptr+0) = a;
	*(ptr+1) = b;
	*(ptr+2) = c;
	*(ptr+3) = 1;
	if (a==t0 && b==t1 && c==t2)
	    *(ptr+3) = 0;
	//-----------------------------------------------
	ptr += 4;
	data += 3;
    }
    return newdata;
}

void check_resize(XEvent *e)
{
    //The ConfigureNotify is sent by the
    //server if the window is resized.
    if (e->type != ConfigureNotify)
	return;
    XConfigureEvent xce = e->xconfigure;
    if (xce.width != gl.xres || xce.height != gl.yres) {
	//Window size did change.
	reshape_window(xce.width, xce.height);
    }
}

void init_opengl(void)
{
    //OpenGL initialization
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    //Initialize matrices
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    //Set 2D mode (no perspective)
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_FOG);
    glDisable(GL_CULL_FACE);	

    //Set the screen background color
    glClearColor(0.1, 0.1, 0.1, 1.0);
    //glClear(GL_COLOR_BUFFER_BIT);
    //Do this to allow fonts
    glEnable(GL_TEXTURE_2D);
    initialize_fonts();
    //
    //==============================================
    // Convertpng2ppm
    //==============================================
    system("convert ./images/mainChar1.png ./images/mainChar1.ppm");
    system("convert ./images/YellowChar.png ./images/yellowchar.ppm");
    system("convert ./images/BlueChar.png ./images/bluechar.ppm");
    system("convert ./images/GreenChar.png ./images/greenchar.ppm");
    system("convert ./images/PurpleChar.png ./images/purplechar.ppm");
    system("convert ./images/BluePortal.png ./images/blueportal.ppm");
    system("convert ./images/OrangePortal.png ./images/orangeportal.ppm");
    system("convert ./images/Timer.png ./images/timer.ppm");
    system("convert ./images/HealthBar.png ./images/healthbar.ppm");
    system("convert ./images/yellowProfile.png ./images/yellowprofile.ppm");
    system("convert ./images/blueProfile.png ./images/blueprofile.ppm");
    system("convert ./images/greenProfile.png ./images/greenprofile.ppm");
    system("convert ./images/purpleProfile.png ./images/purpleprofile.ppm");
    system("convert ./images/charselection.png ./images/charselection.ppm");
    system("convert ./images/colordomination.png ./images/colordomination.ppm");
    system("convert ./images/controls.png ./images/controls.ppm");
    system("convert ./images/credits.png ./images/credits.ppm");
    system("convert ./images/go.png ./images/go.ppm");
    system("convert ./images/heartadd.png ./images/heartadd.ppm");
    system("convert ./images/levelselect.png ./images/levelselect.ppm");
    system("convert ./images/mechabg.png ./images/mechabg.ppm");
    system("convert ./images/menubg.png ./images/menubg.ppm");
    system("convert ./images/one.png ./images/one.ppm");
    system("convert ./images/play.png ./images/play.ppm");
    system("convert ./images/quit.png ./images/quit.ppm");
    system("convert ./images/splatteryellow.png ./images/splatteryellow.ppm");
    system("convert ./images/splatterblue.png ./images/splatterblue.ppm");
    system("convert ./images/splattergreen.png ./images/splattergreen.ppm");
    system("convert ./images/splatterpurple.png ./images/splatterpurple.ppm");
    system("convert ./images/three.png ./images/three.ppm");
    system("convert ./images/two.png ./images/two.ppm");
    system("convert ./images/charselectbg.png ./images/charselectbg.ppm");
    system("convert ./images/ingamebg.png ./images/ingamebg.ppm");
    system("convert ./images/menubg.png ./images/menubg.ppm");
    system("convert ./images/winner.png ./images/winner.ppm");
    system("convert ./images/Tie.png ./images/tie.ppm");
    system("convert ./images/Bomb.png ./images/bomb.ppm");
    system("convert ./images/Fork.png ./images/fork.ppm");
    system("convert ./images/Freeze.png ./images/freeze.ppm");
    system("convert ./images/explosion.png ./images/explosion.ppm");
    //==============================================

    //==============================================
    // Get Images
    //==============================================
    gl.mainchar1Image = ppm6GetImage("./images/mainChar1.ppm");	
    gl.yellowcharImage = ppm6GetImage("./images/yellowchar.ppm");	
    gl.bluecharImage = ppm6GetImage("./images/bluechar.ppm");	
    gl.greencharImage = ppm6GetImage("./images/greenchar.ppm");	
    gl.purplecharImage = ppm6GetImage("./images/purplechar.ppm");	
    gl.blueportalImage = ppm6GetImage("./images/blueportal.ppm");	
    gl.orangeportalImage = ppm6GetImage("./images/orangeportal.ppm");	
    gl.timerImage = ppm6GetImage("./images/timer.ppm");	
    gl.healthbarImage = ppm6GetImage("./images/healthbar.ppm");	
    gl.yellowprofileImage = ppm6GetImage("./images/yellowprofile.ppm");	
    gl.blueprofileImage = ppm6GetImage("./images/blueprofile.ppm");	
    gl.greenprofileImage = ppm6GetImage("./images/greenprofile.ppm");	
    gl.purpleprofileImage = ppm6GetImage("./images/purpleprofile.ppm");	
    gl.charselectionImage = ppm6GetImage("./images/charselection.ppm");	
    gl.colordominationImage = ppm6GetImage("./images/colordomination.ppm");	
    gl.controlsImage = ppm6GetImage("./images/controls.ppm");	
    gl.creditsImage = ppm6GetImage("./images/credits.ppm");	
    gl.goImage = ppm6GetImage("./images/go.ppm");	
    gl.heartaddImage = ppm6GetImage("./images/heartadd.ppm");	
    gl.levelselectImage = ppm6GetImage("./images/levelselect.ppm");	
    gl.mechabgImage = ppm6GetImage("./images/mechabg.ppm");	
    gl.menubgImage = ppm6GetImage("./images/menubg.ppm");	
    gl.oneImage = ppm6GetImage("./images/one.ppm");	
    gl.playImage = ppm6GetImage("./images/play.ppm");	
    gl.quitImage = ppm6GetImage("./images/quit.ppm");	
    gl.splatteryellowImage = ppm6GetImage("./images/splatteryellow.ppm");	
    gl.splatterblueImage = ppm6GetImage("./images/splatterblue.ppm");	
    gl.splattergreenImage = ppm6GetImage("./images/splattergreen.ppm");	
    gl.splatterpurpleImage = ppm6GetImage("./images/splatterpurple.ppm");	
    gl.threeImage = ppm6GetImage("./images/three.ppm");	
    gl.twoImage = ppm6GetImage("./images/two.ppm");	
    gl.charselectbgImage = ppm6GetImage("./images/charselectbg.ppm");	
    gl.ingamebgImage = ppm6GetImage("./images/ingamebg.ppm");	
    gl.menubgImage = ppm6GetImage("./images/menubg.ppm");	
    gl.winnerImage = ppm6GetImage("./images/winner.ppm");	
    gl.tieImage = ppm6GetImage("./images/tie.ppm");	
    gl.bombImage = ppm6GetImage("./images/bomb.ppm");	
    gl.forkImage = ppm6GetImage("./images/fork.ppm");	
    gl.freezeImage = ppm6GetImage("./images/freeze.ppm");	
    gl.explosionImage = ppm6GetImage("./images/explosion.ppm");	
    //==============================================

    //==============================================
    // Generate Textures
    //==============================================
    glGenTextures(1, &gl.mchar1Texture);	
    glGenTextures(1, &gl.yellowcharTexture);	
    glGenTextures(1, &gl.bluecharTexture);	
    glGenTextures(1, &gl.greencharTexture);	
    glGenTextures(1, &gl.purplecharTexture);	
    glGenTextures(1, &gl.blueportalTexture);	
    glGenTextures(1, &gl.orangeportalTexture);	
    glGenTextures(1, &gl.timerTexture);	
    glGenTextures(1, &gl.healthbarTexture);	
    glGenTextures(1, &gl.yellowprofileTexture);	
    glGenTextures(1, &gl.blueprofileTexture);	
    glGenTextures(1, &gl.greenprofileTexture);	
    glGenTextures(1, &gl.purpleprofileTexture);	

    glGenTextures(1, &gl.charselectionTexture);	
    glGenTextures(1, &gl.colordominationTexture);	
    glGenTextures(1, &gl.controlsTexture);	
    glGenTextures(1, &gl.creditsTexture);	
    glGenTextures(1, &gl.goTexture);	
    glGenTextures(1, &gl.heartaddTexture);	
    glGenTextures(1, &gl.levelselectTexture);	
    glGenTextures(1, &gl.mechabgTexture);	
    glGenTextures(1, &gl.menubgTexture);	
    glGenTextures(1, &gl.oneTexture);	
    glGenTextures(1, &gl.playTexture);	
    glGenTextures(1, &gl.quitTexture);	
    glGenTextures(1, &gl.splatteryellowTexture);	
    glGenTextures(1, &gl.splatterblueTexture);	
    glGenTextures(1, &gl.splattergreenTexture);	
    glGenTextures(1, &gl.splatterpurpleTexture);	
    glGenTextures(1, &gl.threeTexture);	
    glGenTextures(1, &gl.twoTexture);	
    glGenTextures(1, &gl.charselectbgTexture);	
    glGenTextures(1, &gl.ingamebgTexture);	
    glGenTextures(1, &gl.menubgTexture);	
    glGenTextures(1, &gl.winnerTexture);	
    glGenTextures(1, &gl.tieTexture);	
    glGenTextures(1, &gl.bombTexture);	
    glGenTextures(1, &gl.forkTexture);	
    glGenTextures(1, &gl.freezeTexture);	
    glGenTextures(1, &gl.explosionTexture);	
    //==============================================

    //==============================================
    // Main Character 1
    int w = gl.mainchar1Image->width;
    int h = gl.mainchar1Image->height;
    glBindTexture(GL_TEXTURE_2D, gl.mchar1Texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *maincharacter1Data = buildAlphaData(gl.mainchar1Image);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, maincharacter1Data);
    free(maincharacter1Data);
    unlink("./images/mainChar1.ppm"); 
    //==============================================

    //==============================================
    // Yellow Char
    w = gl.yellowcharImage->width;
    h = gl.yellowcharImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.yellowcharTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *yellowcharData = buildAlphaData(gl.yellowcharImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, yellowcharData);
    free(yellowcharData);
    unlink("./images/yellowchar.ppm"); 
    //==============================================

    //==============================================
    // Blue Char
    w = gl.bluecharImage->width;
    h = gl.bluecharImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.bluecharTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *bluecharData = buildAlphaData(gl.bluecharImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, bluecharData);
    free(bluecharData);
    unlink("./images/bluechar.ppm"); 
    //==============================================

    //==============================================
    // Green Char
    w = gl.greencharImage->width;
    h = gl.greencharImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.greencharTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *greencharData = buildAlphaData(gl.greencharImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, greencharData);
    free(greencharData);
    unlink("./images/greenchar.ppm"); 
    //==============================================

    //==============================================
    // Purple Char
    w = gl.purplecharImage->width;
    h = gl.purplecharImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.purplecharTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *purplecharData = buildAlphaData(gl.purplecharImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, purplecharData);
    free(purplecharData);
    unlink("./images/purplechar.ppm"); 
    //==============================================

    //==============================================
    // Blue Portal
    w = gl.blueportalImage->width;
    h = gl.blueportalImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.blueportalTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *blueportalData = buildAlphaData(gl.blueportalImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, blueportalData);
    free(blueportalData);
    unlink("./images/blueportal.ppm"); 
    //==============================================

    //==============================================
    // Orange Portal
    w = gl.orangeportalImage->width;
    h = gl.orangeportalImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.orangeportalTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *orangeportalData = buildAlphaData(gl.orangeportalImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, orangeportalData);
    free(orangeportalData);
    unlink("./images/orangeportal.ppm"); 
    //==============================================

    //==============================================
    // Timer Frame
    w = gl.timerImage->width;
    h = gl.timerImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.timerTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *timerData = buildAlphaData(gl.timerImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, timerData);
    free(timerData);
    unlink("./images/timer.ppm"); 
    //==============================================

    //==============================================
    // Health Bar
    w = gl.healthbarImage->width;
    h = gl.healthbarImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.healthbarTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *healthbarData = buildAlphaData(gl.healthbarImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, healthbarData);
    free(healthbarData);
    unlink("./images/healthbar.ppm"); 
    //==============================================

    //==============================================
    // Yellow Profile
    w = gl.yellowprofileImage->width;
    h = gl.yellowprofileImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.yellowprofileTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *yellowprofileData = buildAlphaData(gl.yellowprofileImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, yellowprofileData);
    free(yellowprofileData);
    unlink("./images/yellowprofile.ppm"); 
    //==============================================

    //==============================================
    // Blue Profile
    w = gl.blueprofileImage->width;
    h = gl.blueprofileImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.blueprofileTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *blueprofileData = buildAlphaData(gl.blueprofileImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, blueprofileData);
    free(blueprofileData);
    unlink("./images/blueprofile.ppm"); 
    //==============================================

    //==============================================
    // Green Profile
    w = gl.greenprofileImage->width;
    h = gl.greenprofileImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.greenprofileTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *greenprofileData = buildAlphaData(gl.greenprofileImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, greenprofileData);
    free(greenprofileData);
    unlink("./images/greenprofile.ppm"); 
    //==============================================

    //==============================================
    // Purple Profile
    w = gl.purpleprofileImage->width;
    h = gl.purpleprofileImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.purpleprofileTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *purpleprofileData = buildAlphaData(gl.purpleprofileImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, purpleprofileData);
    free(purpleprofileData);
    unlink("./images/purpleprofile.ppm"); 
    //==============================================

    //==============================================
    // Char Select Text
    w = gl.charselectionImage->width;
    h = gl.charselectionImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.charselectionTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *charselectionData = buildAlphaData(gl.charselectionImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, charselectionData);
    free(charselectionData);
    unlink("./images/charselection.ppm"); 
    //==============================================

    //==============================================
    // ColorDom Text
    w = gl.colordominationImage->width;
    h = gl.colordominationImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.colordominationTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *colordominationData = buildAlphaData(gl.colordominationImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, colordominationData);
    free(colordominationData);
    unlink("./images/colordomination.ppm"); 
    //==============================================

    //==============================================
    // Controls Text
    w = gl.controlsImage->width;
    h = gl.controlsImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.controlsTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *controlsData = buildAlphaData(gl.controlsImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, controlsData);
    free(controlsData);
    unlink("./images/controls.ppm"); 
    //==============================================

    //==============================================
    // Credits Text
    w = gl.creditsImage->width;
    h = gl.creditsImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.creditsTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *creditsData = buildAlphaData(gl.creditsImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, creditsData);
    free(creditsData);
    unlink("./images/credits.ppm"); 
    //==============================================

    //==============================================
    // Go Text
    w = gl.goImage->width;
    h = gl.goImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.goTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *goData = buildAlphaData(gl.goImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, goData);
    free(goData);
    unlink("./images/go.ppm"); 
    //==============================================

    //==============================================
    // Heart Add
    w = gl.heartaddImage->width;
    h = gl.heartaddImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.heartaddTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *heartaddData = buildAlphaData(gl.heartaddImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, heartaddData);
    free(heartaddData);
    unlink("./images/heartadd.ppm"); 
    //==============================================

    //==============================================
    // Level Select Frame
    w = gl.levelselectImage->width;
    h = gl.levelselectImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.levelselectTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *levelselectData = buildAlphaData(gl.levelselectImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, levelselectData);
    free(levelselectData);
    unlink("./images/levelselect.ppm"); 
    //==============================================

    //==============================================
    // Mecha BG
    w = gl.mechabgImage->width;
    h = gl.mechabgImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.mechabgTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *mechabgData = buildAlphaData(gl.mechabgImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, mechabgData);
    free(mechabgData);
    unlink("./images/mechabg.ppm"); 
    //==============================================

    //==============================================
    // Menu BG
    w = gl.menubgImage->width;
    h = gl.menubgImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.menubgTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *menubgData = buildAlphaData(gl.menubgImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, menubgData);
    free(menubgData);
    unlink("./images/menubg.ppm"); 
    //==============================================

    //==============================================
    // One text
    w = gl.oneImage->width;
    h = gl.oneImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.oneTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *oneData = buildAlphaData(gl.oneImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, oneData);
    free(oneData);
    unlink("./images/one.ppm"); 
    //==============================================

    //==============================================
    // Play text
    w = gl.playImage->width;
    h = gl.playImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.playTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *playData = buildAlphaData(gl.playImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, playData);
    free(playData);
    unlink("./images/play.ppm"); 
    //==============================================

    //==============================================
    // Quit text
    w = gl.quitImage->width;
    h = gl.quitImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.quitTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *quitData = buildAlphaData(gl.quitImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, quitData);
    free(quitData);
    unlink("./images/quit.ppm"); 
    //==============================================

    //==============================================
    // Splatter Yellow
    w = gl.splatteryellowImage->width;
    h = gl.splatteryellowImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.splatteryellowTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *splatteryellowData = buildAlphaData(gl.splatteryellowImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, splatteryellowData);
    free(splatteryellowData);
    unlink("./images/splatteryellow.ppm"); 
    //==============================================

    //==============================================
    // Splatter Blue
    w = gl.splatterblueImage->width;
    h = gl.splatterblueImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.splatterblueTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *splatterblueData = buildAlphaData(gl.splatterblueImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, splatterblueData);
    free(splatterblueData);
    unlink("./images/splatterblue.ppm"); 
    //==============================================

    //==============================================
    // Splatter Green
    w = gl.splattergreenImage->width;
    h = gl.splattergreenImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.splattergreenTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *splattergreenData = buildAlphaData(gl.splattergreenImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, splattergreenData);
    free(splattergreenData);
    unlink("./images/splattergreen.ppm"); 
    //==============================================

    //==============================================
    // Splatter Purple
    w = gl.splatterpurpleImage->width;
    h = gl.splatterpurpleImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.splatterpurpleTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *splatterpurpleData = buildAlphaData(gl.splatterpurpleImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, splatterpurpleData);
    free(splatterpurpleData);
    unlink("./images/splatterpurple.ppm"); 
    //==============================================

    //==============================================
    // Three text
    w = gl.threeImage->width;
    h = gl.threeImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.threeTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *threeData = buildAlphaData(gl.threeImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, threeData);
    free(threeData);
    unlink("./images/three.ppm"); 
    //==============================================

    //==============================================
    // Two text
    w = gl.twoImage->width;
    h = gl.twoImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.twoTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *twoData = buildAlphaData(gl.twoImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, twoData);
    free(twoData);
    unlink("./images/two.ppm"); 
    //==============================================

    //==============================================
    // Char select bg
    w = gl.charselectbgImage->width;
    h = gl.charselectbgImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.charselectbgTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *charselectbgData = buildAlphaData(gl.charselectbgImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, charselectbgData);
    free(charselectbgData);
    unlink("./images/charselectbg.ppm"); 
    //==============================================

    //==============================================
    // Ingamebg
    w = gl.ingamebgImage->width;
    h = gl.ingamebgImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.ingamebgTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *ingamebgData = buildAlphaData(gl.ingamebgImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, ingamebgData);
    free(ingamebgData);
    unlink("./images/ingamebg.ppm"); 
    //==============================================
    
    //==============================================
    // Winner
    w = gl.winnerImage->width;
    h = gl.winnerImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.winnerTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *winnerData = buildAlphaData(gl.winnerImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, winnerData);
    free(winnerData);
    unlink("./images/winner.ppm"); 
    //==============================================
    
    //==============================================
    // Tie
    w = gl.tieImage->width;
    h = gl.tieImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.tieTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *tieData = buildAlphaData(gl.tieImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, tieData);
    free(tieData);
    unlink("./images/tie.ppm"); 
    //==============================================
    
    //==============================================
    // Bomb
    w = gl.bombImage->width;
    h = gl.bombImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.bombTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *bombData = buildAlphaData(gl.bombImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, bombData);
    free(bombData);
    unlink("./images/bomb.ppm"); 
    //==============================================
    
    //==============================================
    // Fork
    w = gl.forkImage->width;
    h = gl.forkImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.forkTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *forkData = buildAlphaData(gl.forkImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, forkData);
    free(forkData);
    unlink("./images/fork.ppm"); 
    //==============================================
    
    //==============================================
    // Freeze
    w = gl.freezeImage->width;
    h = gl.freezeImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.freezeTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *freezeData = buildAlphaData(gl.freezeImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, freezeData);
    free(freezeData);
    unlink("./images/freeze.ppm"); 
    //==============================================
    
    //==============================================
    // Explosion
    w = gl.explosionImage->width;
    h = gl.explosionImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.explosionTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *explosionData = buildAlphaData(gl.explosionImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, explosionData);
    free(explosionData);
    unlink("./images/explosion.ppm"); 
    //==============================================
}

void check_mouse(XEvent *e)
{
    static int savex = 0;
    static int savey = 0;
    static int n = 0;

    if (e->type == ButtonRelease) {
	return;
    }
    if (e->type == ButtonPress) {
	if (e->xbutton.button==1) {
	    //Left button was pressed
	    //int y = WINDOW_HEIGHT - e->xbutton.y;	
	    return;
	}
	if (e->xbutton.button==3) {
	    //Right button was pressed
	    return;
	}
    }
    //Did the mouse move?
    if (savex != e->xbutton.x || savey != e->xbutton.y) {
	savex = e->xbutton.x;
	savey = e->xbutton.y;
	if (++n < 10)
	    return;
	//int y = WINDOW_HEIGHT - e->xbutton.y;
	for (int i = 0; i < 10; i++)
	{
	    //makeParticle(game, e->xbutton.x, y);
	}
    }
}

void check_keys(XEvent *e)
{
    //Was there input from the keyboard?
    /*if (e->type == KeyPress) {
      int key = XLookupKeysym(&e->xkey, 0);
      if (key == XK_Escape) {
      return 1;
      }
    //You may check other keys here.
    */
    int key = XLookupKeysym(&e->xkey, 0);
    if (e->type == KeyRelease) {
	gl.keys[key] = 0;
	if (key == XK_Shift_L || key == XK_Shift_R)
	    return;
    }
    if (e->type == KeyPress) {
	gl.keys[key] = 1;
	if (key == XK_Shift_L || key == XK_Shift_R)
	    return;
    } else { 
	return;
    }

    switch(key)
    {
	case XK_Escape:
	    gl.done = 1;
	    break;
#ifdef UNIT_TEST
	case XK_b:
	    setup_screen_res(gl.xres, gl.yres);
	    break;
#endif
	case XK_q:
	    colorChangeFlag = 0;
	    break;
	case XK_v: { 
		       gl.vsync ^= 1;
		       //https://github.com/godotengine/godot/blob/master/platform/x11/context_gl_x11.cpp
		       static PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT = NULL; 
		       glXSwapIntervalEXT =
			   (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddressARB(
				   (const GLubyte *)"glXSwapIntervalEXT");
		       GLXDrawable drawable = glXGetCurrentDrawable();
		       if (gl.vsync) {
			   glXSwapIntervalEXT(dpy, drawable, 1);
		       } else {
			   glXSwapIntervalEXT(dpy, drawable, 0);
		       }
		       break;
		   }
	case XK_f:
		   gl.frameRateOn ^= 1;
		   break;
	case XK_minus:
			//playTitleMusic();
			//titleMusic();
		   char1->health -= 5;
		   break;
	case XK_Tab:
		   if (game.state == STATE_GAMEPLAY) {
		       game.state = STATE_CHARSELECT;
		       gameFrame = 5;			// reset Time when backing out
		       timeoutFrame = timeoutFrame;
		       resetEverything();
		   }
		   if (game.state == STATE_CHARSELECT) {
		       game.state = STATE_STARTMENU;
		   }
		   if (game.state == STATE_CONTROLS) {
		       game.state = STATE_STARTMENU;
		   }
		   if (game.state == STATE_CREDITS) {
		       game.state = STATE_STARTMENU;
		   }
		   break;
	case XK_i:
		   //playDrums();
		   //playApplause();
		   break;
	case XK_Return:
		   // START BUTTON
		   if (game.state == STATE_STARTMENU && gl.cursorLocation == 0) { 
		       game.state = STATE_CHARSELECT;
		       gl.cursorLocation = 0;
		       playSelect();
		       break;
		   }
		   // CONTROLS BUTTON
		   if (game.state == STATE_STARTMENU && gl.cursorLocation == 1) { 
		       game.state = STATE_CONTROLS;
		       gl.cursorLocation = 1;
		       playSelect();
		       break;
		   }
		   // CREDITS BUTTON
		   if (game.state == STATE_STARTMENU && gl.cursorLocation == 2) { 
		       game.state = STATE_CREDITS;
		       gl.cursorLocation = 2;
		       playSelect();
		       break;
		   }
		   // EXIT BUTTON
		   if (game.state == STATE_STARTMENU && gl.cursorLocation == 3) { 
		       game.state = STATE_GAMEOVER;
		       gl.done = 1;
		       playSelect();
		       break;
		   }
		   // Approve Char select
		   if (game.state == STATE_CHARSELECT &&
			   gl.cursorLocation != gl.cursorLocation2) {
		       startCountdown();
		       checkCountdown();
		       game.state = STATE_GAMEPLAY;
		       break;
		   }
		   break;
	case XK_space:
		   break;
	case XK_equal:
		   gl.delay -= 0.005;
		   if (gl.delay < 0.005)
		       gl.delay = 0.005;
	case XK_Up:
		   if (game.state == STATE_STARTMENU) {
		       playScroll();
		       if (gl.cursorLocation != 0) {
			   gl.cursorLocation -= 1;
		       }
		   }
		   if (game.state == STATE_CHARSELECT) {
		       playScroll();
		       if (gl.cursorLocation2 > 1) {
			   gl.cursorLocation2 -= 2;
		       }
		   }
		   break;
	case XK_Down:
		   if (game.state == STATE_STARTMENU) {
		       playScroll();
		       if (gl.cursorLocation != 3) {
			   gl.cursorLocation += 1;
		       }
		   }
		   if (game.state == STATE_CHARSELECT) {
		       playScroll();
		       if (gl.cursorLocation2 < 2) {
			   gl.cursorLocation2 += 2;
		       }
		   }
		   break;
	case XK_Left: 
		   if (game.state == STATE_CHARSELECT) {
		       playScroll();
		       if (gl.cursorLocation2 != 0) {
			   gl.cursorLocation2 -= 1;
		       }
		   }
		   break;
	case XK_Right: 
		   if (game.state == STATE_CHARSELECT) {
		       playScroll();
		       if (gl.cursorLocation2 != 3) {
			   gl.cursorLocation2 += 1;
		       }
		   }
		   break;
	case XK_w:
		   if (game.state == STATE_CHARSELECT) {
		       playScroll();
		       if (gl.cursorLocation > 1 ) {
			   gl.cursorLocation -= 2;
		       }
		   }
		   break;
	case XK_s:
		   if (game.state == STATE_CHARSELECT) {
		       playScroll();
		       if (gl.cursorLocation < 2) {
			   gl.cursorLocation += 2;
		       }
		   }
		   break;
	case XK_d:
		   if (game.state == STATE_CHARSELECT) {
		       playScroll();
		       if (gl.cursorLocation != 3) {
			   gl.cursorLocation += 1;
		       }
		   }
		   break;
	case XK_a:
		   if (game.state == STATE_CHARSELECT) {
		       playScroll();
		       if (gl.cursorLocation != 0) {
			   gl.cursorLocation -= 1;
		       }
		   }
		   break;
    }		
}

void physics(Game *game)
{
    if (game->state == STATE_GAMEPLAY) {
	if (gl.cursorLocation == 0)
	    char1->colorID = 1;		// YELLOW
	if (gl.cursorLocation == 1)
	    char1->colorID = 2;	
	if (gl.cursorLocation == 2)
	    char1->colorID = 3;	
	if (gl.cursorLocation == 3)
	    char1->colorID = 4;	

	if (gl.cursorLocation2 == 0)
	    char2->colorID = 1;		// YELLOW
	if (gl.cursorLocation2 == 1)
	    char2->colorID = 2;	
	if (gl.cursorLocation2 == 2)
	    char2->colorID = 3;	
	if (gl.cursorLocation2 == 3)
	    char2->colorID = 4;	

	//char1->colorID = 1;		// YELLOW
	//char2->colorID = 2;         // BLUE

	if (char1->inAirBool) {
	    //char1->vel.y = 0.2*gravity;
	    if (char1->vel.y > -9)
		char1->vel.y += gravity/16;
	}

	if (char2->inAirBool) {
	    //char1->vel.y = 0.2*gravity;
	    if (char2->vel.y > -9)
		char2->vel.y += gravity/16;
	}

	// COLLISION
	int boxTop[90], boxBot[90], boxLeft[90], boxRight[90];

	for (int i = 0; i < totalCubes; i++) {
	    Shape *s = &game->box[i];
	    boxTop[i] = s->center.y + s->height + (char1->height-5);
	    boxBot[i] = s->center.y - s->height - (char1->height-10);
	    boxLeft[i] = s->center.x - s->width - (char1->width-10);
	    boxRight[i] = s->center.x + s->width + (char1->width-10);
	}

	for (int i = 0; i < totalCubes; i++) {
	    Shape *s = &game->box[i];
	    if (char1->cy < boxTop[i] && char1->cy > boxBot[i]) {
		if (char1->cx > boxLeft[i] && char1->cx < boxRight[i]) {
		    // Top Collision
		    if (char1->cy < boxTop[i] &&
			    char1->cy > boxTop[i] - 10 &&
			    char1->cx < boxRight[i] - 10 &&
			    char1->cx > boxLeft[i] + 10) {
			char1->cy = boxTop[i];
			char1->inAirBool = false;
			char1->jumpCount = 1;
			char1->vel.y = -1;	
			colorChangeFlag = 1;

			// Point System 
			awardPoint(char1, s);    
			removePoint(char2, char2, s);    

			// Save box index # and location
			boxIndex = i;
			globalSaveBox = s;
			s->boxColorID = char1->colorID;
		    } else {
			char1->inAirBool = true;
		    }
		    // Bot Collision
		    if (char1->cy > boxBot[i] &&
			    char1->cy < boxBot[i] + 10 &&
			    char1->cx < boxRight[i] - 10 &&
			    char1->cx > boxLeft[i] + 10) {
			char1->cy = boxBot[i];
			char1->vel.y = -3;

			colorChangeFlag = 1;

			// Point System 
			awardPoint(char1, s);    
			removePoint(char2, char2, s);    

			// Save box index # and location
			boxIndex = i;
			globalSaveBox = s;
			s->boxColorID = char1->colorID;
		    }
		    // Right Collision
		    if (char1->cx < boxRight[i] && 
			    char1->cx > s->center.x &&
			    char1->cy < boxTop[i] - 10 &&
			    char1->cy > boxBot[i] + 10) {
			char1->cx = boxRight[i];
			//colorChangeFlag = 1;

			colorChangeFlag = 1;

			// Point System 
			awardPoint(char1, s);    
			removePoint(char2, char2, s);    

			// Save box index # and location
			boxIndex = i;
			globalSaveBox = s;
			s->boxColorID = char1->colorID;
		    }
		    // Left Collision
		    if (char1->cx > boxLeft[i] &&
			    char1->cx < s->center.x &&
			    char1->cy < boxTop[i] - 10 &&
			    char1->cy > boxBot[i] + 10) {
			char1->cx = boxLeft[i];
			//colorChangeFlag = 1;

			colorChangeFlag = 1;

			// Point System 
			awardPoint(char1, s);    
			removePoint(char2, char2, s);    

			// Save box index # and location
			boxIndex = i;
			globalSaveBox = s;
			s->boxColorID = char1->colorID;
		    }
		}
	    }
	}

	// Player Collision char2
	for (int i = 0; i < totalCubes; i++) {
	    Shape *s = &game->box[i];
	    if (char2->cy < boxTop[i] && char2->cy > boxBot[i]) {
		if (char2->cx > boxLeft[i] && char2->cx < boxRight[i]) {
		    // Top Collision
		    if (char2->cy < boxTop[i] &&
			    char2->cy > boxTop[i] - 10 &&
			    char2->cx < boxRight[i] - 10 &&
			    char2->cx > boxLeft[i] + 10) {
			char2->cy = boxTop[i];
			char2->inAirBool = false;
			char2->jumpCount = 1;
			char2->vel.y = -1;	
			colorChangeFlag = 2;

			// Point System 
			awardPoint(char2, s);    
			removePoint(char1, char1, s);    

			// Save box index # and location
			boxIndex = i;
			globalSaveBox = s;
			s->boxColorID = char2->colorID;
		    } else {
			char2->inAirBool = true;
		    }
		    // Bot Collision
		    if (char2->cy > boxBot[i] &&
			    char2->cy < boxBot[i] + 10 &&
			    char2->cx < boxRight[i] - 10 &&
			    char2->cx > boxLeft[i] + 10) {
			char2->cy = boxBot[i];
			char2->vel.y = -3;

			colorChangeFlag = 2;

			// Point System 
			awardPoint(char2, s);    
			removePoint(char1, char1, s);    

			// Save box index # and location
			boxIndex = i;
			globalSaveBox = s;
			s->boxColorID = char2->colorID;
		    }
		    // Right Collision
		    if (char2->cx < boxRight[i] && 
			    char2->cx > s->center.x &&
			    char2->cy < boxTop[i] - 10 &&
			    char2->cy > boxBot[i] + 10) {
			char2->cx = boxRight[i];
			//colorChangeFlag = 1;

			colorChangeFlag = 2;

			// Point System 
			awardPoint(char2, s);    
			removePoint(char1, char1, s);    

			// Save box index # and location
			boxIndex = i;
			globalSaveBox = s;
			s->boxColorID = char2->colorID;
		    }
		    // Left Collision
		    if (char2->cx > boxLeft[i] &&
			    char2->cx < s->center.x &&
			    char2->cy < boxTop[i] - 10 &&
			    char2->cy > boxBot[i] + 10) {
			char2->cx = boxLeft[i];
			//colorChangeFlag = 1;

			colorChangeFlag = 2;

			// Point System 
			awardPoint(char2, s);    
			removePoint(char1, char1, s);    

			// Save box index # and location
			boxIndex = i;
			globalSaveBox = s;
			s->boxColorID = char2->colorID;
		    }
		}
	    } 
	}


	// Blue Portal Collision
	if (char1->cy < 425 && char1->cy > 380) {
	    if (char1->cx > 20 && char1->cx < 45) {
		// translate location
		char1->cx = 1190;
		char1->cy = 400;
	    }
	}
	// char 2
	if (char2->cy < 425 && char2->cy > 380) {
	    if (char2->cx > 20 && char2->cx < 45) {
		// translate location
		char2->cx = 1190;
		char2->cy = 400;
	    }
	}
	//
	// Orange Portal Collision
	if (char1->cy < 425 && char1->cy > 380) {
	    if (char1->cx > 1220 && char1->cx < 1250) {
		// translate location
		char1->cx = 55;
		char1->cy = 400;
	    }
	}
	// char 2
	if (char2->cy < 425 && char2->cy > 380) {
	    if (char2->cx > 1220 && char2->cx < 1250) {
		// translate location
		char2->cx = 55;
		char2->cy = 400;
	    }
	}
	//	

	//printf("Char 1 facing: %d\n", char1->facingLeft);
	//printf("Char 2 facing: %d\n", char2->facingLeft);
	// Player 1 Movement Keys
	if (gl.keys[XK_d]) {
	    //leftFaceChar1 = 0;
	    char1->facingLeft = 0;
	    char1->cx += 8;
	}

	if (gl.keys[XK_a]) {
	    //leftFaceChar1 = 1;
	    char1->facingLeft = 1;
	    char1->cx += -8;
	}

	if (gl.keys[XK_w] && char1->jumpCount == 1) {
	    jump(char1);
	}
	// Player 2 Movement Keys
	if (gl.keys[XK_Right]) {
	    //leftFaceChar2 = 0;
	    char2->facingLeft = 0;
	    char2->cx += 8;
	}

	if (gl.keys[XK_Left]) {
	    //leftFaceChar2 = 1;
	    char2->facingLeft = 1;
	    char2->cx += -8;
	}

	if (gl.keys[XK_Up] && char2->jumpCount == 1 ) {
	    jump(char2);
	}
	//

	// Player 1 Animation
	if (gl.keys[XK_d]) {
	    //leftFaceChar1 = 0;
	    //man is walking...
	    //when time is up, advance the frame.
	    timers.recordTime(&timers.timeCurrent);
	    double timeSpan = timers.timeDiff(&timers.yellowcharTime, &timers.timeCurrent);
	    if (timeSpan > gl.delay) {
		//advance
		++gl.yellowcharFrame;
		if (gl.yellowcharFrame >= 2)
		    gl.yellowcharFrame -= 2;
		timers.recordTime(&timers.yellowcharTime);
	    }
	}

	if (gl.keys[XK_a]) {
	    //leftFaceChar1 = 1;
	    //man is walking...
	    //when time is up, advance the frame.
	    timers.recordTime(&timers.timeCurrent);
	    double timeSpan = timers.timeDiff(&timers.yellowcharTime, &timers.timeCurrent);
	    if (timeSpan > gl.delay) {
		//advance
		++gl.yellowcharFrame;
		if (gl.yellowcharFrame >= 2)
		    gl.yellowcharFrame -= 2;
		timers.recordTime(&timers.yellowcharTime);
	    }
	}

	// Player 2 Animation 
	if (gl.keys[XK_Right]) {
	    //leftFaceChar2 = 0;
	    //man is waling...
	    //when time is up, advance the frame.
	    timers.recordTime(&timers.timeCurrent);
	    double timeSpan = timers.timeDiff(&timers.bluecharTime, &timers.timeCurrent);
	    if (timeSpan > gl.delay) {
		//advance
		++gl.bluecharFrame;
		if (gl.bluecharFrame >= 2)
		    gl.bluecharFrame -= 2;
		timers.recordTime(&timers.bluecharTime);
	    }
	}

	if (gl.keys[XK_Left]) {
	    //leftFaceChar2 = 1;
	    //man is walking...
	    //when time is up, advance the frame.
	    timers.recordTime(&timers.timeCurrent);
	    double timeSpan = timers.timeDiff(&timers.bluecharTime, &timers.timeCurrent);
	    if (timeSpan > gl.delay) {
		//advance
		++gl.bluecharFrame;
		if (gl.bluecharFrame >= 2)
		    gl.bluecharFrame -= 2;
		timers.recordTime(&timers.bluecharTime);
	    }
	}

	physicsPortal();

	//==============================================
	// bullet physics
	//==============================================
	/*if (gl.keys[XK_space] && game.state == STATE_GAMEPLAY) {
	    struct timespec bt;
	    clock_gettime(CLOCK_REALTIME, &bt);
	    double ts = timeDiff(&g.bulletTimer, &bt);
	    if (ts > 0.5) {
		memcpy(&g.barr[i], &g.barr[g.bullets-1], sizeof(Bullet));
		g.nbullets--;
		continue;
	    }
	    b->pos[0] += 5;
	    b->pos[1] += 0;
	    i++;
	}*/

	//==============================================
	// bullet done
	//==============================================

	// Jump Update
	heartCollision(char1);
	heartCollision(char2);
	char1->cy += char1->vel.y;
	char2->cy += char2->vel.y;
    }
}

void physicsPortal() 
{
    if (gameFrame > 0) {
	timers.recordTime(&timers.timeCurrent);
	double timeSpan = timers.timeDiff(&timers.blueportalTime, &timers.timeCurrent);
	if (timeSpan > gl.delay + 0.5) {
	    //advance
	    ++gl.blueportalFrame;
	    if (gl.blueportalFrame >= 2)
		gl.blueportalFrame -= 2;
	    timers.recordTime(&timers.blueportalTime);
	}
    }

    if (gameFrame > 0) {
	timers.recordTime(&timers.timeCurrent);
	double timeSpan = timers.timeDiff(&timers.orangeportalTime, &timers.timeCurrent);
	if (timeSpan > gl.delay + 0.5) {
	    //advance
	    ++gl.orangeportalFrame;
	    if (gl.orangeportalFrame >= 2)
		gl.orangeportalFrame -= 2;
	    timers.recordTime(&timers.orangeportalTime);
	}
    }

}
void jump(Character *player) 
{
    if (!player->inAirBool || player->jumpCount == 1) {
	player->vel.y = 14;
	player->inAirBool = true;
	player->jumpCount = 0;
    }
}

const float DEG2RAD = 3.14159/180;

void drawCircle(float radius)
{
    glBegin(GL_TRIANGLE_FAN);

    for (int i = 0; i < 360; i++) {
	float degInRad = i*DEG2RAD;
	if (char1->points > char2->points) { 
	    glColor3ub(160,160,160);
	    //glColor3ub(255,255,0);
	    /*if (char1->colorID == 1) {			// YELLOW
		glColor3ub(255,255,0);
	    } 
	    if (char1->colorID == 2) {			// BLUE
		glColor3ub(69,255,255);
	    }
	    if (char1->colorID == 3) {
		glColor3ub(155,238,46);			// GREEN
	    }
	    if (char1->colorID == 4) {	    
		glColor3ub(216,12,225);			// PURPLE
	    }*/
	} else if (char1->points < char2->points) {
	    glColor3ub(160,160,160);
	    //glColor3ub(19,13,255);
	    /*if (char2->colorID == 1) {			// YELLOW
		glColor3ub(255,255,0);
	    } 
	    if (char2->colorID == 2) {			// BLUE
		glColor3ub(69,255,255);
	    }
	    if (char2->colorID == 3) {
		glColor3ub(155,238,46);			// GREEN
	    }
	    if (char2->colorID == 4) {	    
		glColor3ub(216,12,225);			// PURPLE
	    }*/
	}
	else
	    glColor3ub(100,100,100);

	glVertex2f(cos(degInRad)*radius + gl.xres/2, sin(degInRad)*radius + gl.yres-50);
    }

    glEnd();
}

void heartCollision(Character *player)
{
    if (!gl.heartFlag) {
	float xleft = gl.xres/2-45;
	float xright = gl.xres/2+45;
	float ytop = gl.yres/2+110;
	float ybot = gl.yres/2+90;

	if (player->cx > xleft && player->cx < xright &&
		player->cy > ybot && player->cy < ytop) {
	    if (player->health < 53) {
		gl.heartFlag = 1;
		player->health += 5; 
	    }
	}       
    }
}

void resetEverything()
{
    timeoutFrame = 0;
    gameFrame = 5;
    gl.cursorLocation = 0;
    initializeFlag = 1;
    one = true;
    two = true;
    three = true;
    go = true;
    
    char1->cx = 210;
    char2->cx = 1080;
    char1->cy = gl.yres/2 + 15;
    char2->cy = gl.yres/2 + 15;
    char1->points = 0;
    char2->points = 0;
}

void countdown() 
{
    Rect r;
    unsigned int c = 0x000000;
    r.bot = gl.yres - 60;
    r.left = (gl.xres/2-10);
    r.center = 0;
    timers.recordTime(&timers.timeCurrent);
    double timeSpan = timers.timeDiff(&timers.gameTime, &timers.timeCurrent);
    if (timeSpan > gameDelay && gameFrame > 0 && !go) {
	//advance
	--gameFrame;
	timers.recordTime(&timers.gameTime);
    }
    if (gameFrame == 0)
    {
	if (timeoutFrame < 2) {
	    if (bellFlag) {
		playBell();
		bellFlag = 0;
	    }
	}

	timers.recordTime(&timers.timeCurrent);
	double timeSpan = timers.timeDiff(&timers.timeOut, &timers.timeCurrent);
	if (timeSpan > gameDelay) {
	    ++timeoutFrame;
	    timers.recordTime(&timers.timeOut);
	}
	if (timeoutFrame >= 2 && timeoutFrame < 4) {
	    // DRUM ROLL MUSIC HERE	
	    if (drumsFlag) {
		playDrums();
		drumsFlag = 0;
	    }
	}
	if (timeoutFrame > 4 && timeoutFrame <= 8) {
	    // APPLAUSE MUSIC HERE
	    if (appFlag) {
	    	playApplause();
		appFlag = 0;
	    }
	    drawWinner();
	}

	if (timeoutFrame > 8) { 
	    game.state = STATE_STARTMENU;
	    // Reset Everything
	    resetEverything();
	}

	//gameFrame = 0;
	/*printf("GAME OVER\n");
	if (char1->points > char2->points)
	    printf("Player 1 WINS\n");
	else if (char2->points > char1->points)
	    printf("Player 2 WINS\n");
	else 
	    printf("TIE\n");*/
    }
    ggprint16(&r, 32, c, "%02i", gameFrame);
}	

void changeColor(Character *player, Shape *box)
{
    if (player->colorID == 1) {			// YELLOW
	glColor3ub(255,255,0);
    } 
    if (player->colorID == 2) {			// BLUE
	glColor3ub(69,255,255);
    }
    if (player->colorID == 3) {
	glColor3ub(155,238,46);			// GREEN
    }
    if (player->colorID == 4) {	    
	glColor3ub(216,12,225);			// PURPLE
    }

    Shape *s;
    s = box;
    glPushMatrix();
    //s.center.x = 60*i + 40;
    //s.center.y = 60;
    //glTranslatef(s[i].center.x, s[i].center.y, s[i].center.z);
    //cout << box->center.x << endl;
    glTranslatef(box->center.x, box->center.y, box->center.z);
    int w = s->width;
    int h = s->height;
    glBegin(GL_QUADS);
    glVertex2i(-w, -h);
    glVertex2i(-w, h);
    glVertex2i( w, h);
    glVertex2i( w, -h);
    glEnd();
    glPopMatrix();
}

void awardPoint(Character *player, Shape *s) 
{
    if (player->colorID != s->boxColorID) {
	player->points++;
	if (player->health < 49)
	    player->health += 5;	
	printf("Player Health: %d\n", player->health);	
	cout << "Player " << player->colorID << " Points: " << player->points << endl;
    }
}

void removePoint(Character *player, Character *player2, Shape *s) 
{
    if (player->colorID == s->boxColorID && s->boxColorID != 0) {
	player->points--;
	if (player2->health > 0)
	    player2->health -= 5;
	printf("Player 2 Health: %d\n", player2->health);	
	cout << "Player " << player->colorID << " Points: " << player->points << endl;
    }
}

void render(Game *game)
{
    if (game->state == STATE_STARTMENU)
	drawStartMenu();

    if (game->state == STATE_CHARSELECT) 
	drawCharSelectMenu();

    if (game->state == STATE_CONTROLS)
	drawControlsMenu();
    
    if (game->state == STATE_CREDITS)
	drawCredits();

    if (game->state == STATE_GAMEPLAY)
    {
	float w, h;
	glClear(GL_COLOR_BUFFER_BIT);

	//renderViewport(0, gl.xres, gl.yres);

	//Draw shapes...
	Shape *s;

	//==============================================
	// Draw Map
	//
	// draw ingame background
	rWithoutAlpha(gl.mechabgTexture, gl.xres, gl.yres);

	// BOTTOM SCREEN
	// Init map first
	if (initializeFlag) { 
	    for (int i = 1; i < totalCubes; i++) {
		glColor3ub(100,100,100);

		s = &game->box[i];
		s->boxColorID = 0;
		//cout << s->boxColorID << endl;
		glPushMatrix();
		glTranslatef(game->box[i].center.x, game->box[i].center.y, game->box[i].center.z);
		w = s->width;
		h = s->height;
		glBegin(GL_QUADS);
		glVertex2i(-w, -h);
		glVertex2i(-w, h);
		glVertex2i( w, h);
		glVertex2i( w, -h);
		glEnd();
		glPopMatrix();
	    }
	}
	initializeFlag = 0;

	// Changing Color
	for (int i = 1; i < totalCubes; i++) {
	    s = &game->box[i];
	    if (colorChangeFlag == 1 && boxIndex == i /*&& char1->colorID != s->boxColorID*/) {
		changeColor(char1, globalSaveBox);
		//awardPoint(pointFlag);
		//pointFlag = false;
	    } else if (colorChangeFlag == 2 && boxIndex == i) {
		changeColor(char2, globalSaveBox);
	    } else if (s->boxColorID == 1) {
		glColor3ub(255,255,0);
	    } else if (s->boxColorID == 2) {
		glColor3ub(69,255,255);
	    } else if (s->boxColorID == 3) {
		glColor3ub(155,238,46);
	    } else if (s->boxColorID == 4) {
		glColor3ub(216,12,225);
	    } else {
		glColor3ub(100,100,100);
	    }

	    glPushMatrix();
	    glTranslatef(game->box[i].center.x, game->box[i].center.y, game->box[i].center.z);
	    w = s->width;
	    h = s->height;
	    glBegin(GL_QUADS);
	    glVertex2i(-w, -h);
	    glVertex2i(-w, h);
	    glVertex2i( w, h);
	    glVertex2i( w, -h);
	    glEnd();
	    glPopMatrix();
	}


	if (gl.cursorLocation == 0) { 
	    gl.tempTexture = gl.yellowcharTexture;
	    gl.tempProfileTexture = gl.yellowprofileTexture;
	}
	if (gl.cursorLocation == 1) {
	    gl.tempTexture = gl.bluecharTexture;
	    gl.tempProfileTexture = gl.blueprofileTexture;	
	}
	if (gl.cursorLocation == 2) {
	    gl.tempTexture = gl.greencharTexture;
	    gl.tempProfileTexture = gl.greenprofileTexture;
	}
	if (gl.cursorLocation == 3) {
	    gl.tempTexture = gl.purplecharTexture;
	    gl.tempProfileTexture = gl.purpleprofileTexture;
	}

	if (gl.cursorLocation2 == 0) {
	    gl.tempTexture2 = gl.yellowcharTexture;
	    gl.tempProfileTexture2 = gl.yellowprofileTexture;
	}
	if (gl.cursorLocation2 == 1) {
	    gl.tempTexture2 = gl.bluecharTexture;
	    gl.tempProfileTexture2 = gl.blueprofileTexture;
	}
	if (gl.cursorLocation2 == 2) {
	    gl.tempTexture2 = gl.greencharTexture;
	    gl.tempProfileTexture2 = gl.greenprofileTexture;
	}
	if (gl.cursorLocation2 == 3) {
	    gl.tempTexture2 = gl.purplecharTexture;
	    gl.tempProfileTexture2 = gl.purpleprofileTexture;
	}


	// UI DRAWING
	drawPlayerOne(gl.tempTexture);
	drawPlayerTwo(gl.tempTexture2);
	drawBluePortal();
	drawOrangePortal();
	drawTimerBackground();
	drawHealthBar1();
	drawHealthBar2();
	drawHealthVal1();
	drawHealthVal2();
	drawCircleUI1();
	drawCircleUI2();
	drawProfile1(gl.tempProfileTexture);
	drawProfile2(gl.tempProfileTexture2);
	drawCircle(30);
	countdown();

	// Heart
	if (gl.heartFlag || gameFrame == 0)
	    rWithAlpha(30, 30, gl.xres/2-1000, gl.yres/2+100, gl.heartaddTexture);	
	else
	    rWithAlpha(30, 30, gl.xres/2, gl.yres/2+100, gl.heartaddTexture);	

	//
	drawFrameRate();
	//printf("Left Char 1: %d\n", leftFaceChar1);
	//	printf("Left Char 2: %d\n", leftFaceChar2);
	
	//====================================
	// COUNTDOWN BEFORE GAME	
	clock_gettime(CLOCK_REALTIME, &timers.countdown_current);
	int timediff = timers.countdown_current.tv_sec - timers.countdown_start.tv_sec;
	if (timediff < 1) {
	    if (three) {
		playThree();
		three = false;
	    }
	    countdown3(gl.xres/2,gl.yres/2);
	}
	if (timediff < 2 && timediff >= 1) {
	    if (two) {
		playTwo();
		two = false;
	    }
	    countdown2(gl.xres/2,gl.yres/2);
	}
	if (timediff < 3 && timediff >= 2) {
	    if (one) {
		playOne();
		one = false;
	    }
	    countdown1(gl.xres/2,gl.yres/2);
	}
	if (timediff < 4 && timediff >= 3) {
	    if (go) {
		playGo();
		go = false;
	    }
	    countdowngo(gl.xres/2,gl.yres/2);
	}
	//====================================
	//Bullet *b = &g.barr[0];
	//for (int i = 0; i < g.nbullets; i++) {
	//    drawBullet(char1, gl.forkTexture);
	//    ++b;
	//}
	if (gl.keys[XK_space])
	    drawBullet(char1, gl.forkTexture);
    }
}

void drawBullet(Character *player, GLuint forkTexture) 
{
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(player->cx, player->cy, 0);
    glBindTexture(GL_TEXTURE_2D, forkTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int w = 30.0f;
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-w);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,w);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,w);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-w);
    glEnd();
    glPopMatrix();
    glDisable(GL_ALPHA_TEST);	
}

void drawStartMenu()
{
    float h = 40;
    float w = 170;
    float multiplier = 1.25;

    //gl.cursorLocation = 0;

    // background of start menu
    rWithoutAlpha(gl.menubgTexture, gl.xres, gl.yres);

    //printf("Cursor value: %d\n", gl.cursorLocation); 
    // draw splatter left
    rWithAlpha(60, 60, gl.xres/4 + 40, 400-(gl.cursorLocation*100), gl.splattergreenTexture);	
    // draw splatter right
    rWithAlpha(60, 60, gl.xres*3/4 -50, 400-(gl.cursorLocation*100), gl.splattergreenTexture);	

    // draw title text
    rWithAlpha(90, 500, gl.xres/2, 580, gl.colordominationTexture);	

    // draw play text
    if (gl.cursorLocation == 0) {
	rWithAlpha(h*multiplier, w*multiplier, gl.xres/2, 400, gl.playTexture);
    } else {	
	rWithAlpha(h, w, gl.xres/2, 400, gl.playTexture);
    }   
    // draw controls text
    if (gl.cursorLocation == 1) {
	rWithAlpha(h*multiplier, w*multiplier, gl.xres/2, 300, gl.controlsTexture);
    } else {	
	rWithAlpha(h, w, gl.xres/2, 300, gl.controlsTexture);
    }    
    // draw credits text
    if (gl.cursorLocation == 2) {
	rWithAlpha(h*multiplier, w*multiplier, gl.xres/2, 200, gl.creditsTexture);
    } else {
	rWithAlpha(h, w, gl.xres/2, 200, gl.creditsTexture);
    }
    // draw quit text
    if (gl.cursorLocation == 3) {
	rWithAlpha(h*multiplier, w*multiplier, gl.xres/2, 100, gl.quitTexture);
    } else {    
	rWithAlpha(h, w, gl.xres/2, 100, gl.quitTexture);
    }    
}

void drawControlsMenu()
{
    float w, h;
    glClear(GL_COLOR_BUFFER_BIT);

    // Top Square
    w = 450;
    h = 100;
    glPushMatrix();
    glColor3f(0.7,0.0,0.0);
    glTranslatef(gl.xres/2, gl.yres*3/4, 0);
    glAlphaFunc(GL_GREATER, 0.0f);
    //glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glVertex2i(-w,-h);
    glVertex2i(-w,h);
    glVertex2i(w,h);
    glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
	
    // Left Square
    w = 230;
    h = 170;
    glPushMatrix();
    glColor3f(0.0,0.7,0.0);
    glTranslatef(gl.xres/4+100, gl.yres/3+30, 0);
    glAlphaFunc(GL_GREATER, 0.0f);
    //glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glVertex2i(-w,-h);
    glVertex2i(-w,h);
    glVertex2i(w,h);
    glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    
    // Right Square
    w = 230;
    h = 170;
    glPushMatrix();
    glColor3f(0.0,0.0,0.7);
    glTranslatef(gl.xres*3/4-100, gl.yres/3+30, 0);
    glAlphaFunc(GL_GREATER, 0.0f);
    //glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glVertex2i(-w,-h);
    glVertex2i(-w,h);
    glVertex2i(w,h);
    glVertex2i(w,-h);
    glEnd();
    glPopMatrix();

    //===================================
    // Objective instructions
    Rect r;
    unsigned int c = 0xFFFFFFFF;
    r.bot = gl.yres - 125;
    r.left = gl.xres/2-50;
    r.center = 0;
    ggprint16(&r, 32, c, "Objective:");
    
    r.bot = gl.yres - 165;
    r.left = gl.xres/3-28;
    r.center = 0;
    ggprint16(&r, 32, c, "Touching a tile will change its color to the player's color.");
    
    r.bot = gl.yres - 205;
    r.left = gl.xres/3-130;
    r.center = 0;
    ggprint16(&r, 32, c, "The color of a tile can be changed by another player after being painted a color.");
    
    r.bot = gl.yres - 245;
    r.left = gl.xres/3-118;
    r.center = 0;
    ggprint16(&r, 32, c, "The player with the most tiles that are their color by the end of the time wins.");
    //===================================
    
    //===================================
    // Player one control instructions
    r.bot = gl.yres - 350;
    r.left = gl.xres*2/8;
    r.center = 0;
    ggprint16(&r, 32, c, "Player One Controls");
    
    r.bot = gl.yres - 410;
    r.left = gl.xres*2/8;
    r.center = 0;
    ggprint16(&r, 32, c, "W - Jump");
    
    r.bot = gl.yres - 460;
    r.left = gl.xres*2/8;
    r.center = 0;
    ggprint16(&r, 32, c, "A - Move Left");
    
    r.bot = gl.yres - 510;
    r.left = gl.xres*2/8;
    r.center = 0;
    ggprint16(&r, 32, c, "D - Move Right");
    //===================================
    
    //===================================
    // Player two control instructions
    r.bot = gl.yres - 350;
    r.left = gl.xres*5/8-50;
    r.center = 0;
    ggprint16(&r, 32, c, "Player Two Controls");
    
    r.bot = gl.yres - 410;
    r.left = gl.xres*5/8-50;
    r.center = 0;
    ggprint16(&r, 32, c, "Up Arrow Key - Jump");
    
    r.bot = gl.yres - 460;
    r.left = gl.xres*5/8-50;
    r.center = 0;
    ggprint16(&r, 32, c, "Left Arrow Key - Move Left");
    
    r.bot = gl.yres - 510;
    r.left = gl.xres*5/8-50;
    r.center = 0;
    ggprint16(&r, 32, c, "Right Arrow Key - Move Right");
    //===================================
}
 
void drawCredits()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    Rect r;
    unsigned int c = 0xFFFFFFFF;
    r.bot = gl.yres/2;
    r.left = gl.xres/2-50;
    r.center = 0;
    ggprint16(&r, 10, c, "Rodrigo made it");
}

void drawWinner() 
{
    Rect r; 
    float h = gl.yres;
    float w = gl.xres;
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.08,0.08,0.08,0.9);
    glTranslated(gl.xres/2, gl.yres/2, 0);
    glBegin(GL_QUADS);
    glVertex2i(-w, -h);
    glVertex2i(-w,  h);
    glVertex2i(w,   h);
    glVertex2i(w,  -h);
    glEnd();
    glDisable(GL_BLEND);
    glPopMatrix();
   
    // WINNER TOP 
    if (char1->points == char2->points)
	rWithAlpha(60, 150, gl.xres/2, 580, gl.tieTexture);	
    else
	rWithAlpha(60, 325, gl.xres/2, 580, gl.winnerTexture);	
    
    // draw Left Bar
    Shape s;
    Shape leftBar[100];
    for (int i = 0; i < char1->points; i++) {
	leftBar[i].width = 100;
	leftBar[i].height = 5;
	leftBar[i].center.x = gl.xres/3;
	leftBar[i].center.y = 65 + (i*9);
	leftBar[i].center.z = 0;
	s = leftBar[i];
	glPushMatrix();
	if (char1->colorID == 1) {			// YELLOW
	    glColor3ub(255,255,0);
	} 
	if (char1->colorID == 2) {			// BLUE
	    glColor3ub(69,255,255);
	}
	if (char1->colorID == 3) {
	    glColor3ub(155,238,46);			// GREEN
	}
	if (char1->colorID == 4) {	    
	    glColor3ub(216,12,225);			// PURPLE
	}
	glTranslatef(s.center.x, s.center.y, s.center.z);
	float w = s.width;
	float h = s.height;
	glBegin(GL_QUADS);
	glVertex2i(-w, -h);
	glVertex2i(-w, h);
	glVertex2i(w, h);
	glVertex2i(w, -h);
	glEnd();
	glPopMatrix();
    
    }	
    // draw Right Bar
    Shape rightBar[100];
    for (int i = 0; i < char2->points; i++) {
	rightBar[i].width = 100;
	rightBar[i].height = 5;
	rightBar[i].center.x = gl.xres*2/3;
	rightBar[i].center.y = 65 + (i*9);
	rightBar[i].center.z = 0;
	s = rightBar[i];
	glPushMatrix();
	if (char2->colorID == 1) {			// YELLOW
	    glColor3ub(255,255,0);
	} 
	if (char2->colorID == 2) {			// BLUE
	    glColor3ub(69,255,255);
	}
	if (char2->colorID == 3) {
	    glColor3ub(155,238,46);			// GREEN
	}
	if (char2->colorID == 4) {	    
	    glColor3ub(216,12,225);			// PURPLE
	}
	glTranslatef(s.center.x, s.center.y, s.center.z);
	float w = s.width;
	float h = s.height;
	glBegin(GL_QUADS);
	glVertex2i(-w, -h);
	glVertex2i(-w, h);
	glVertex2i(w, h);
	glVertex2i(w, -h);
	glEnd();
	glPopMatrix();
	
    }	

    // draw player1 at top of bar
    sCharPose(gl.xres/3, leftBar[char1->points-1].center.y+100, 75, 75, gl.tempTexture, gl.yellowcharFrame%2, 1);
    // draw player2 at top of bar
    sCharPose(gl.xres*2/3, rightBar[char2->points-1].center.y+100, 75, 75, gl.tempTexture2, gl.yellowcharFrame%2, 1);


    //unsigned int c = 0xFFFFFFFF;
    unsigned int c = 0x00000000;
    // draw player1 text
    r.bot = leftBar[char1->points/2 - 1].center.y;
    r.left = gl.xres/3;
    r.center = 1; 
    ggprint16(&r, 50, c, "%d", char1->points);

    // draw player1 text
    r.bot = rightBar[char2->points/2 - 1].center.y;
    r.left = gl.xres*2/3;
    r.center = 1; 
    ggprint16(&r, 50, c, "%d", char2->points);
}

void drawCharSelectMenu()
{
    int w, h;
    w = 150; 
    h = 150; 
    //printf("Cursor value2: %d\n", gl.cursorLocation2); 

    // draw char select background
    rWithoutAlpha(gl.charselectbgTexture, gl.xres, gl.yres);
    // draw char select text
    rWithAlpha(80, 500, gl.xres/2, 580, gl.charselectionTexture);	

    // draw player one left splatter
    if (gl.cursorLocation == 0) {
	rWithAlpha(w, h, gl.xres/6-40, gl.yres/2-100, gl.splatteryellowTexture);	
	rWithAlpha(w-20, h-20, gl.xres/3+50, 375, gl.splatteryellowTexture);	
    }
    if (gl.cursorLocation == 1) {
	rWithAlpha(w, h, gl.xres/6-40, gl.yres/2-100, gl.splatterblueTexture);	
	rWithAlpha(w-20, h-20, gl.xres*2/3-50, 375, gl.splatterblueTexture);	
    }
    if (gl.cursorLocation == 2) {
	rWithAlpha(w, h, gl.xres/6-40, gl.yres/2-100, gl.splattergreenTexture);	
	rWithAlpha(w-20, h-20, gl.xres/3+50, 150, gl.splattergreenTexture);	
    }
    if (gl.cursorLocation == 3) {
	rWithAlpha(w, h, gl.xres/6-40, gl.yres/2-100, gl.splatterpurpleTexture);	
	rWithAlpha(w-20, h-20, gl.xres*2/3-50, 150, gl.splatterpurpleTexture);	
    }
    // draw player two right splatter
    if (gl.cursorLocation2 == 0) {
	rWithAlpha(w, h, gl.xres*5/6+40, gl.yres/2-100, gl.splatteryellowTexture);	
	rWithAlpha(w-20, h-20, gl.xres/3+50, 375, gl.splatteryellowTexture);	
    }
    if (gl.cursorLocation2 == 1) {
	rWithAlpha(w, h, gl.xres*5/6+40, gl.yres/2-100, gl.splatterblueTexture);	
	rWithAlpha(w-20, h-20, gl.xres*2/3-50, 375, gl.splatterblueTexture);	
    }
    if (gl.cursorLocation2 == 2) {
	rWithAlpha(w, h, gl.xres*5/6+40, gl.yres/2-100, gl.splattergreenTexture);	
	rWithAlpha(w-20, h-20, gl.xres/3+50, 150, gl.splattergreenTexture);	
    }
    if (gl.cursorLocation2 == 3) {
	rWithAlpha(w, h, gl.xres*5/6+40, gl.yres/2-100, gl.splatterpurpleTexture);	
	rWithAlpha(w-20, h-20, gl.xres*2/3-50, 150, gl.splatterpurpleTexture);	
    }
    //
    // draw frame top left
    renderFrame(80, 80, gl.xres/3+50, 375, gl.levelselectTexture);
    // draw frame top right
    renderFrame(80, 80, gl.xres*2/3-50, 375, gl.levelselectTexture);
    // draw frame bot left
    renderFrame(80, 80, gl.xres/3+50, 150, gl.levelselectTexture);
    // draw frame bot right
    renderFrame(80, 80, gl.xres*2/3-50, 150, gl.levelselectTexture);
    // draw top left char
    sCharPose(gl.xres/3+50, 380, 55, 55, gl.yellowcharTexture, gl.yellowcharFrame%2, 1);
    // draw top right char
    sCharPose(gl.xres*2/3-50, 380, 55, 55, gl.bluecharTexture, gl.bluecharFrame%2, 1);
    // draw bot left char
    sCharPose(gl.xres/3+50, 155, 55, 55, gl.greencharTexture, gl.greencharFrame%2, 1);
    // draw bot right char
    sCharPose(gl.xres*2/3-50, 155, 55, 55, gl.purplecharTexture, gl.purplecharFrame%2, 1);


    // draw p1 text
    rWithAlpha(70, 40, gl.xres/6-40, gl.yres/2-100, gl.oneTexture);	
    // draw p2 text
    rWithAlpha(70, 50, gl.xres*5/6+40, gl.yres/2-100, gl.twoTexture);	
}

void sCharPose(int cx, int cy, int h, int w, GLuint texture, int ix, int iy)
{
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(ix + .5, iy+1); glVertex2i(cx+w,cy-h);
    glTexCoord2f(ix      , iy+1); glVertex2i(cx-w,cy-h);
    glTexCoord2f(ix      , iy       ); glVertex2i(cx-w,cy+h);
    glTexCoord2f(ix + .5, iy       ); glVertex2i(cx+w,cy+h);
    glEnd();
    glPopMatrix();
} 

void startCountdown()
{
    clock_gettime(CLOCK_REALTIME, &timers.countdown_start);
    one = true;
    two = true;
    three = true;
}

bool checkCountdown() 
{    
    clock_gettime(CLOCK_REALTIME, &timers.countdown_current);
    int timediff = timers.countdown_current.tv_sec - timers.countdown_start.tv_sec;
    if (timediff < 1) {
	if (three) {
	    playThree();
	    three = false;
	}
	countdown3(800,600);
	return false;
    }
    if (timediff < 2 && timediff >= 1) {
	if (two) {
	    playTwo();
	    two = false;
	}
	countdown2(800,600);
	return false;
    }
    if (timediff < 3 && timediff >= 2) {
	if (one) {
	    playOne();
	    one = false;
	}
	countdown1(800,600);
	return true;
    }
    if (timediff < 4 && timediff >= 3) {
	if (go) {
	    playGo();
	    go = false;
	}
	countdowngo(gl.xres/2,gl.yres/2);
    }
    return true;
}

void countdown3(int xres, int yres)
{
    rWithAlpha(100, 60, xres, yres, gl.threeTexture);	
}	

void countdown2(int xres, int yres)
{
    rWithAlpha(100, 60, xres, yres, gl.twoTexture);	
}	

void countdown1(int xres, int yres)
{
    rWithAlpha(100, 60, xres, yres, gl.oneTexture);	
}	

void countdowngo(int xres, int yres)
{
    rWithAlpha(100, 140, xres, yres, gl.goTexture);	
}	

void renderFrame(int h, int w, int trans_x, int trans_y, GLuint texture) 
{
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(trans_x, trans_y, 0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
}

void rWithAlpha(int h, int w, int trans_x, int trans_y, GLuint texture) 
{
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(trans_x, trans_y, 0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    glDisable(GL_ALPHA_TEST);	
}

void rWithoutAlpha(GLuint texture, int xres, int yres)
{
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(0,0);
    glTexCoord2f(0.0, 0.0); glVertex2i(0,yres);
    glTexCoord2f(1.0, 0.0); glVertex2i(xres,yres);
    glTexCoord2f(1.0, 1.0); glVertex2i(xres,0);
    glEnd();
    glPopMatrix();        
}

void drawFrameRate() 
{
    if (gl.frameRateOn) {
	// Frame Rate	
	Rect r;
	unsigned int c = 0x002d88d8;
	r.bot = gl.yres - 40;
	r.left = (50);
	r.center = 0;
	ggprint16(&r, 32, c, "Frame Rate : %f", fps);
    }
}

void drawPlayerOne(GLuint tempTexture) 
{
    // CHARACTER
    //
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    //glBindTexture(GL_TEXTURE_2D, gl.yellowcharTexture);
    glBindTexture(GL_TEXTURE_2D, tempTexture);
    //
    //~ if (gl.keys[XK_a])
		//~ glRotatef(10.0f, 0.0, 0.0, 1.0);
    //~ if (gl.keys[XK_d])
		//~ glRotatef(-10.0f, 0.0, 0.0, 1.0);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ix = gl.yellowcharFrame % 2;
    int iy = 1;
    if (gl.yellowcharFrame >= 2)
	iy = 0;
    float tx = (float)ix / 2.0;
    float ty = (float)iy / 1.0;

    //int result;
    int size = 45;
    // Player 1 Draw
    glTranslated(char1->cx, char1->cy,0);
    if (gl.keys[XK_a])
		glRotatef(8.0f, 0.0, 0.0, 1.0);
    if (gl.keys[XK_d])
		glRotatef(-8.0f, 0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    if (gl.keys[XK_d] || !char1->facingLeft)
    {
	//printf("Left Char 1: %d\n", leftFaceChar1);
	//printf("Left Char 2: %d\n", leftFaceChar2);
	glTexCoord2f(tx + .5, ty + 1); glVertex2i(size,  -size);
	glTexCoord2f(tx,       ty + 1); glVertex2i(-size ,-size);
	glTexCoord2f(tx,              ty); glVertex2i( -size , size);
	glTexCoord2f(tx + .5, ty);        glVertex2i(size , size );
	//leftFaceChar2 = 0;
    }

    if (gl.keys[XK_a] || char1->facingLeft)
    {
	//printf("Left Char 1: %d\n", leftFaceChar1);
	//printf("Left Char 2: %d\n", leftFaceChar2);
	//~ glTexCoord2f(tx + .5, ty + 1); glVertex2i(char1->cx - char1->width, char1->cy - char1->height);
	//~ glTexCoord2f(tx + .5,        ty); glVertex2i(char1->cx - char1->width, char1->cy + char1->height);
	//~ glTexCoord2f(tx,              ty); glVertex2i(char1->cx + char1->width, char1->cy + char1->height);
	//~ glTexCoord2f(tx, ty + 1);       glVertex2i(char1->cx + char1->width, char1->cy - char1->height);
	//leftFaceChar2 = 1;
	glTexCoord2f(tx + .5, ty + 1); glVertex2i(-size, -size);
	glTexCoord2f(tx + .5,        ty); glVertex2i(-size, size);
	glTexCoord2f(tx,              ty); glVertex2i(size, size);
	glTexCoord2f(tx, ty + 1);       glVertex2i(size, -size);
    }
    
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST); 	
}

void drawPlayerTwo(GLuint tempTexture2)
{
    // Player 2    
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, tempTexture2);
    //
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ix = gl.bluecharFrame % 2;
    int iy = 1;
    if (gl.bluecharFrame >= 2)
	iy = 0;
    float tx = (float)ix / 2.0;
    float ty = (float)iy / 1.0;
    
    int size = 45;
    glTranslated(char2->cx, char2->cy,0);
    if (gl.keys[XK_Left])
		glRotatef(8.0f, 0.0, 0.0, 1.0);
    if (gl.keys[XK_Right])
		glRotatef(-8.0f, 0.0, 0.0, 1.0);

    glBegin(GL_QUADS);
    if (gl.keys[XK_Right] || !char2->facingLeft)
    {
	glTexCoord2f(tx + .5, ty + 1); glVertex2i(size,  -size);
	glTexCoord2f(tx,       ty + 1); glVertex2i(-size ,-size);
	glTexCoord2f(tx,              ty); glVertex2i( -size , size);
	glTexCoord2f(tx + .5, ty);        glVertex2i(size , size );
	//leftFaceChar1 = 0;
    }

    if (gl.keys[XK_Left] || char2->facingLeft)
    {
	glTexCoord2f(tx + .5, ty + 1); glVertex2i(-size, -size);
	glTexCoord2f(tx + .5,        ty); glVertex2i(-size, size);
	glTexCoord2f(tx,              ty); glVertex2i(size, size);
	glTexCoord2f(tx, ty + 1);       glVertex2i(size, -size);
	//leftFaceChar1 = 1;
    }
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST); 	
}

void drawBluePortal() 
{
    // Draw BluePortal
    float cx = 40;
    float cy = 400;
    float h = 60;
    float w = 60;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.blueportalTexture);
    //
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    float ix = gl.blueportalFrame % 2;
    float iy = 1;
    if (gl.blueportalFrame >= 2)
	iy = 0;
    float tx = (float)ix / 2.0;
    float ty = (float)iy / 1.0;
    // Draw
    glBegin(GL_QUADS);
    glTexCoord2f(tx + .5, ty + 1); glVertex2i(w+cx,h+cy);
    glTexCoord2f(tx,       ty + 1); glVertex2i(-w+cx, h+cy);
    glTexCoord2f(tx,              ty); glVertex2i(-w+cx, -h+cy);
    glTexCoord2f(tx + .5, ty);        glVertex2i(w+cx, -h+cy);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST); 	
    //
}

void drawOrangePortal()
{
    // Draw OrangePortal
    float cx = 1240;
    float cy = 400;
    float h = 60;
    float w = 60;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.orangeportalTexture);
    //
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    float ix = gl.orangeportalFrame % 2;
    float iy = 1;
    if (gl.orangeportalFrame >= 2)
	iy = 0;
    float tx = (float)ix / 2.0;
    float ty = (float)iy / 1.0;
    // Draw
    glBegin(GL_QUADS);
    glTexCoord2f(tx + .5, ty + 1); glVertex2i(-w+cx, h+cy);
    glTexCoord2f(tx,       ty + 1); glVertex2i(w+cx,h+cy);
    glTexCoord2f(tx,              ty); glVertex2i(w+cx, -h+cy);
    glTexCoord2f(tx + .5, ty);        glVertex2i(-w+cx, -h+cy);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST); 	
    //
}

void drawTimerBackground() 
{
    // Draw Timer Background
    float cx = gl.xres/2;
    float cy = gl.yres - 50;
    float h = 38;
    float w = 38;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.timerTexture);
    //
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    // Draw
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex2i(-w+cx, h+cy);
    glTexCoord2f(0, 1); glVertex2i(w+cx,h+cy);
    glTexCoord2f(0, 0); glVertex2i(w+cx, -h+cy);
    glTexCoord2f(1, 0); glVertex2i(-w+cx, -h+cy);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST); 	
    //

}

void drawCircleUI1() 
{
    // Draw Timer Background
    float cx = 150;
    float cy = 65;
    float h = 60;
    float w = 60;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.timerTexture);
    //
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    // Draw
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex2i(-w+cx, h+cy);
    glTexCoord2f(0, 1); glVertex2i(w+cx,h+cy);
    glTexCoord2f(0, 0); glVertex2i(w+cx, -h+cy);
    glTexCoord2f(1, 0); glVertex2i(-w+cx, -h+cy);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST); 	
    //

}

void drawCircleUI2() 
{
    // Draw Timer Background
    float cx = gl.xres/2 + 50;
    float cy = 65;
    float h = 60;
    float w = 60;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.timerTexture);
    //
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    // Draw
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex2i(-w+cx, h+cy);
    glTexCoord2f(0, 1); glVertex2i(w+cx,h+cy);
    glTexCoord2f(0, 0); glVertex2i(w+cx, -h+cy);
    glTexCoord2f(1, 0); glVertex2i(-w+cx, -h+cy);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST); 	
    //

}

void drawHealthBar1() 
{
    // Draw Timer Background
    float cx = 380;
    float cy = 65;
    float h = 50;
    float w = 210;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.healthbarTexture);
    //
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    // Draw
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex2i(-w+cx, h+cy);
    glTexCoord2f(0, 1); glVertex2i(w+cx,h+cy);
    glTexCoord2f(0, 0); glVertex2i(w+cx, -h+cy);
    glTexCoord2f(1, 0); glVertex2i(-w+cx, -h+cy);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST); 	
    //

}

void drawHealthBar2() 
{
    // Draw Timer Background
    float cx = 920;
    float cy = 65;
    float h = 50;
    float w = 210;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.healthbarTexture);
    //
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    // Draw
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex2i(-w+cx, h+cy);
    glTexCoord2f(0, 1); glVertex2i(w+cx,h+cy);
    glTexCoord2f(0, 0); glVertex2i(w+cx, -h+cy);
    glTexCoord2f(1, 0); glVertex2i(-w+cx, -h+cy);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST); 	
    //

}

void drawProfile1(GLuint tempProfileTexture) 
{
    // Draw Timer Background
    float cx = 150;
    float cy = 65;
    float h = 46;
    float w = 46;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, tempProfileTexture);
    //
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    // Draw
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex2i(w+cx, -h+cy);
    glTexCoord2f(0, 1); glVertex2i(-w+cx, -h+cy);
    glTexCoord2f(0, 0); glVertex2i(-w+cx,h+cy);
    glTexCoord2f(1, 0); glVertex2i(w+cx, h+cy);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST); 	
    //

}

void drawProfile2(GLuint tempProfileTexture2) 
{
    // Draw Timer Background
    float cx = gl.xres/2 + 50;
    float cy = 65;
    float h = 50;
    float w = 50;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, tempProfileTexture2);
    //
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    // Draw
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex2i(w+cx, -h+cy);
    glTexCoord2f(0, 1); glVertex2i(-w+cx, -h+cy);
    glTexCoord2f(0, 0); glVertex2i(-w+cx,h+cy);
    glTexCoord2f(1, 0); glVertex2i(w+cx, h+cy);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST); 	
    //

}

void drawHealthVal1()
{
    Shape s;
    Shape boxes[100];
    for (int i = 0; i < char1->health; i++) {
	boxes[i].width = 3;
	boxes[i].height = 39;
	boxes[i].center.x = 198 + (i*7);
	boxes[i].center.y = 65;
	boxes[i].center.z = 0;
	s = boxes[i];
	glPushMatrix();
	glColor3ub(255-(4.9*i), 4.9*i, 0);
	glTranslatef(s.center.x, s.center.y, s.center.z);
	float w = s.width;
	float h = s.height;
	glBegin(GL_QUADS);
	glVertex2i(-w, -h);
	glVertex2i(-w, h);
	glVertex2i(w, h);
	glVertex2i(w, -h);
	glEnd();
	glPopMatrix();
    }	
}

void drawHealthVal2()
{
    Shape s;
    Shape boxes[100];
    for (int i = 0; i < char2->health; i++) {
	boxes[i].width = 3;
	boxes[i].height = 39;
	boxes[i].center.x = 737 + (i*7);
	boxes[i].center.y = 65;
	boxes[i].center.z = 0;
	s = boxes[i];
	glPushMatrix();
	glColor3ub(255-(4.9*i), 4.9*i, 0);
	glTranslatef(s.center.x, s.center.y, s.center.z);
	float w = s.width;
	float h = s.height;
	glBegin(GL_QUADS);
	glVertex2i(-w, -h);
	glVertex2i(-w, h);
	glVertex2i(w, h);
	glVertex2i(w, -h);
	glEnd();
	glPopMatrix();
    }	
}
