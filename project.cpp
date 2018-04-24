
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
#endif
#include "ppm.h"
#include "fonts.h"
#include "project.h"                    // header file
using namespace std;

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 720
#define GRAVITY 0.1

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
bool leftFaceChar1 = 0; 
bool leftFaceChar2 = 0; 
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
float finalJumpCy;
float jumpStartCy;
int boxIndex;
int gameFrame = 30;
int gameDelay = 1;
int totalCubes;

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
void check_mouse(XEvent *e, Game *game);
void check_keys(XEvent *e);
void physics(Game *game);
void render(Game *game);

// ==============================================
// Functions
// ==============================================
void jump(Character *);
void checkJump();
void changeColor(Character*, Shape*);
void awardPoint(Character*, Shape*);
void removePoint(Character*, Shape*);
void playerCollision(Character*);
// ==============================================

// ==============================================
// Ppm Images
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
	srand(time(NULL));
	//initXWindows();
	//init_opengl();

	//declare game object
	//Game game;
	char1 = &game.player[0];
	char2 = &game.player[1];
	char1->cx = 210;
	char2->cx = 920;
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
			game.box[i].center.y = 490;
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
			game.box[i].center.y = 490;
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


	while (!gl.done) {
		while (XPending(dpy)) {
			XEvent e;
			XNextEvent(dpy, &e);
			check_resize(&e);
			check_mouse(&e, &game);
			check_keys(&e);
		}
        if (gameFrame > 0)
		    physics(&game);
		render(&game);
		glXSwapBuffers(dpy, win);
		showFrameRate();
	}
	cleanupXWindows();
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

}

void makeParticle(Game *game, int x, int y)
{
	if (game->n >= MAX_PARTICLES)
		return;
	//std::cout << "makeParticle() " << x << " " << y << std::endl;
	//position of particle
	Particle *p = &game->particle[game->n];
	p->s.center.x = x;
	p->s.center.y = y;
	p->velocity.y = rnd() * 2.0 - 1.0;
	p->velocity.x = rnd() * 2.0 - 1.0;
	game->n++;
}

void check_mouse(XEvent *e, Game *game)
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
			int y = WINDOW_HEIGHT - e->xbutton.y;	
			makeParticle(game, e->xbutton.x, y);
			makeParticle(game, e->xbutton.x, y);
			makeParticle(game, e->xbutton.x, y);
			makeParticle(game, e->xbutton.x, y);
			makeParticle(game, e->xbutton.x, y);
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
		int y = WINDOW_HEIGHT - e->xbutton.y;
		for (int i = 0; i < 10; i++)
		{
			makeParticle(game, e->xbutton.x, y);
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
		case XK_w:
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
        case XK_equal:
                   gl.delay -= 0.005;
                   if (gl.delay < 0.005)
					   gl.delay = 0.005;
				   break;
		case XK_minus:
				   gl.delay += 0.005;
				   break;
	}		
}

//void physics(Game *game)
//{
//Particle *p;
/*
   if (game->n <= 0)
   return;

   for (int i = 0; i < game->n; i++)
   {
   char1 = &game->player[0];
//p = &game->particle[i];
char1->vel.y -= GnRAVITY;
//p->s.center.x += p->velocity.x;
//p->s.center.y += p->velocity.y;


//check for collision with shapes...
//Shape *s = &game->box[0];

// Need shape
if ( char1->cx < s[i].center.y + 25 && 
char1->cx > s[i].center.x - 25 &&
char1->cx < s[i].center.x + 25)
{	
char1->cy = s[i].center.y + 25;
//char1->velocity.y = -p->velocity.y;
//p->velocity.y *= 0.5;
}	
// Need shape
if ( char1->cx < s[i]->center.y + s[i]->height && 
p->s.center.x > s->center.x - s->width &&
p->s.center.x < s->center.x + s->width)
{	
p->s.center.y = s->center.y + s->height;
p->velocity.y = -p->velocity.y;
p->velocity.y *= 0.5;
}	

//check for off-screen
if (p->s.center.y < 0.0 || p->s.center.y > WINDOW_HEIGHT) {
//std::cout << "off screen" << std::endl;
game->particle[i] = game->particle[game->n-1];
game->n--;
}
}
*/  

//
//collision detect character and boxes
/*for (int i = 0; i < game->n; i++) {
  if ( char1->cx < s[i].center.y + 25 && 
  char1->cx > s[i].center.x - 25 &&
  char1->cx < s[i].center.x + 25) {
  char1->cy = s[i].center.y + 25;
  }
  }*/

// Practice collision GOOD
//if (char1->cy - char1->height < 85) 
//	char1->cy = char1->height + 60 + 25/2;

/*for (int i = 0; i < game->n; i++) {
//char1->cy -= 1;
for (int j = 0; j < 200; j++) {
if (char1->cy < s[j].center.y + s[j].height &&		// checks top
char1->cy > s[j].center.y - s[j].height &&		// checks bottom
char1->cx > s[j].center.x - s[j].width &&		// check leftside
char1->cx < s[j].center.x + s[j].width) {		// check rightside
char1->cy = s[j].center.y + s[j].height;
//char1->cx = s[j].center.x + s[j].width;
}
}
}*/

// Collision getting good
/*for (int j = 1; j < 48; j++) {
  s = &game->box[j];
  printf("Value char1 cx: %f\n", char1->cx);
  printf("Value char1 cy: %f\n", char1->cy);
  printf("Value index 15: center is %f\n", game->box[15].center.y);
  printf("Value index 15: height is %f\n", game->box[15].height);
  if (char1->cy < (char1->height-5) + s->center.y + s->height) {		// checks top
  char1->cy = char1->height-10 + s->center.y + s->height;
//printf("COLLISION\n");

glColor3ub(255,0,250);
s = &game->box[15];
glPushMatrix();
s[15].center.x = 50*15 + 40;
s[15].center.y = 60;
glTranslatef(s[15].center.x, s[15].center.y, s[15].center.z);
float w = s->width;
float h = s->height;
glBegin(GL_QUADS);
glVertex2i(-w, -h);
glVertex2i(-w, h);
glVertex2i( w, h);
glVertex2i( w, -h);
glEnd();
glPopMatrix();
}
}*/

void physics(Game *game)
{
	char1->colorID = 1;		// YELLOW
	char2->colorID = 2;         // BLUE

	/*if (char1inAirBool) {
		char1->cy += char1->vel.y; 
	}

	if (char2inAirBool) {
		char2->cy += char2->vel.y; 
	}*/

	// this is good
	//char1->cy += 0.2*gravity;
	//char2->cy += 0.2*gravity;


	if (char1inAirBool) {
	    //char1->vel.y = 0.2*gravity;
	    if (char1->vel.y > -10)
	    	char1->vel.y += gravity/8;
	}
	char2->vel.y += 0.2*gravity;


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
					gravityOn = false;
					char1inAirBool = false;
					char1->vel.y = -1;	
					colorChangeFlag = 1;

					// Point System 
					awardPoint(char1, s);    
					removePoint(char2, s);    

					// Save box index # and location
					boxIndex = i;
					globalSaveBox = s;
					s->boxColorID = char1->colorID;
				}
				// Bot Collision
				if (char1->cy > boxBot[i] &&
						char1->cy < boxBot[i] + 10 &&
						char1->cx < boxRight[i] - 10 &&
						char1->cx > boxLeft[i] + 10) {
					char1->cy = boxBot[i];
					//colorChangeFlag = 1;
					//char1->vel.y = -0.1;	


					colorChangeFlag = 1;

					// Point System 
					awardPoint(char1, s);    
					removePoint(char2, s);    

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
					//char1->vel.y = -0.1;	


					colorChangeFlag = 1;

					// Point System 
					awardPoint(char1, s);    

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
					//char1->vel.y = -0.1;	


					colorChangeFlag = 1;

					// Point System 
					awardPoint(char1, s);    
					removePoint(char2, s);    

					// Save box index # and location
					boxIndex = i;
					globalSaveBox = s;
					s->boxColorID = char1->colorID;
				}
			}
		}
	}

	playerCollision(char2);

	// Player 1 Movement Keys
	if (gl.keys[XK_Right]) {
		char1->cx += 8;
	}

	if (gl.keys[XK_Left]) {
		char1->cx += -8;
	}

	//if (gl.keys[XK_Up] && !inAirBool) {
	if (gl.keys[XK_Up] && !char1inAirBool) {
		jump(char1);
		//checkJump();
		//char1->vel.y = 5;
		//inAirBool = true;
		char1->cy += 8;
		//gravityOn = true;
	}

	if (gl.keys[XK_Down]) 
		char1->cy += -8;

	// Player 2 Movement Keys
	if (gl.keys[XK_d]) {
		char2->cx += 8;
	}

	if (gl.keys[XK_a]) {
		char2->cx += -8;
	}

	//if (gl.keys[XK_Up] && !inAirBool) {
	if (gl.keys[XK_w]) {
		//jump();
		//checkJump();

		//inAirBool = true;
		char2->cy += 8;
		//gravityOn = true;
	}

	if (gl.keys[XK_s]) 
		char2->cy += -8;


	// Player 1 Animation
	if (gl.keys[XK_Right]) {
		leftFaceChar1 = 0;
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

	if (gl.keys[XK_Left]) {
		leftFaceChar1 = 1;
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
	if (gl.keys[XK_d]) {
		leftFaceChar2 = 0;
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

	if (gl.keys[XK_a]) {
		leftFaceChar2 = 1;
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

    // Jump Updatei
    //printf("Char 1 vel y: %f\n", char1->vel.y);
    char1->cy += char1->vel.y;

}

void playerCollision(Character *player)
{
	int boxTop[90], boxBot[90], boxLeft[90], boxRight[90];

	for (int i = 0; i < totalCubes; i++) {
		//Shape *s = &game->box[i];
		Shape *s = &game.box[i];
		boxTop[i] = s->center.y + s->height + (player->height-5);
		boxBot[i] = s->center.y - s->height - (player->height-10);
		boxLeft[i] = s->center.x - s->width - (player->width-10);
		boxRight[i] = s->center.x + s->width + (player->width-10);
	}

	for (int i = 0; i < totalCubes; i++) {
		//Shape *s = &game->box[i];
		Shape *s = &game.box[i];
		if (player->cy < boxTop[i] && player->cy > boxBot[i]) {
			if (player->cx > boxLeft[i] && player->cx < boxRight[i]) {
				// Top Collision
				if (player->cy < boxTop[i] &&
						player->cy > boxTop[i] - 10 &&
						player->cx < boxRight[i] - 10 &&
						player->cx > boxLeft[i] + 10) {
					player->cy = boxTop[i];
					gravityOn = false;
					char2inAirBool = false;
					colorChangeFlag = 2;

					// Point System 
					awardPoint(player, s);    
					removePoint(char1, s);    

					// Save box index # and location
					boxIndex = i;
					globalSaveBox = s;
					s->boxColorID = player->colorID;
				}
				// Bot Collision
				if (player->cy > boxBot[i] &&
						player->cy < boxBot[i] + 10 &&
						player->cx < boxRight[i] - 10 &&
						player->cx > boxLeft[i] + 10) {
					player->cy = boxBot[i];

					colorChangeFlag = 2;

					// Point System 
					awardPoint(player, s);    
					removePoint(char1, s);    

					// Save box index # and location
					boxIndex = i;
					globalSaveBox = s;
					s->boxColorID = player->colorID;
				}
				// Right Collision
				if (player->cx < boxRight[i] && 
						player->cx > s->center.x &&
						player->cy < boxTop[i] - 10 &&
						player->cy > boxBot[i] + 10) {
					player->cx = boxRight[i];

					colorChangeFlag = 2;

					// Point System 
					awardPoint(player, s);    
					removePoint(char1, s);    

					// Save box index # and location
					boxIndex = i;
					globalSaveBox = s;
					s->boxColorID = player->colorID;
				}
				// Left Collision
				if (player->cx > boxLeft[i] &&
						player->cx < s->center.x &&
						player->cy < boxTop[i] - 10 &&
						player->cy > boxBot[i] + 10) {
					player->cx = boxLeft[i];

					colorChangeFlag = 2;

					// Point System 
					awardPoint(player, s);    
					removePoint(char1, s);    

					// Save box index # and location
					boxIndex = i;
					globalSaveBox = s;
					s->boxColorID = player->colorID;
				}
			}
		}
	}
}

void jump(Character *player) 
{
    if (!char1inAirBool) {
    	player->vel.y = 10;
	char1inAirBool = true;
    }
}

/*float rate = .0006;

void checkJump() 
{
    //printf("Char cy: %f\n", char1->cy);
    //printf("Final cy: %f\n", finalJumpCy);

    //if (inAirBool) {
    // jumping up
    if (jumpStartCy <= finalJumpCy) {
	char1->vel.y = 3.0;
	//char1->vel.y += 1;
	//gravityOn = false;
	//char1->vel.y = 6;
	printf("Char cy: %f\n", char1->cy);
	printf("Final cy: %f\n", finalJumpCy);
	printf("JumpStart cy: %f\n", jumpStartCy);
	printf("FinalJump cy: %f\n", finalJumpCy);
	jumpStartCy = finalJumpCy;
	printf("jumping up\n");
    }
    // jumping down
    if (char1->cy >= finalJumpCy) {
	printf("jumping down\n");
	char1->vel.y = 0;
	char1->cy += GRAVITY;
    }
    //}
}*/

const float DEG2RAD = 3.14159/180;

void drawCircle(float radius)
{
	glBegin(GL_TRIANGLE_FAN);

	for (int i = 0; i < 360; i++) {
		float degInRad = i*DEG2RAD;
		//float degInRad = DEG2RAD*gameFrame;
		if (char1->points > char2->points) 
            glColor3ub(255,255,0);
        else if (char1->points < char2->points)
            glColor3ub(30,144,255);
        else
            glColor3ub(128,128,128);
		
        glVertex2f(cos(degInRad)*radius + gl.xres/2, sin(degInRad)*radius + gl.yres-50);
	}

	glEnd();
}

void countdown() 
{
	Rect r;
	unsigned int c = 0x000000;
	r.bot = gl.yres - 60;
	r.left = (gl.xres/2-10);
	r.center = 0;
	//if (gl.state == STATE_GAMEPLAY) {
	timers.recordTime(&timers.timeCurrent);
	double timeSpan = timers.timeDiff(&timers.gameTime, &timers.timeCurrent);
	if (timeSpan > gameDelay && gameFrame > 0) {
		//advance
		--gameFrame;
		timers.recordTime(&timers.gameTime);
	}
	if (gameFrame == 0)
	{
		//++gl.minutes;
		gameFrame = 0;
		printf("GAME OVER\n");
		if (char1->points > char2->points)
			printf("Player 1 WINS\n");
		else if (char2->points > char1->points)
			printf("Player 2 WINS\n");
		else 
			printf("TIE\n");
	}
	//}
	ggprint16(&r, 32, c, "%02i", gameFrame);
}	

void changeColor(Character *player, Shape *box)
{
	if (player->colorID == 1) {			// YELLOW
		glColor3ub(255,255,0);
	} 
	if (player->colorID == 2) {			// BLUE
		glColor3ub(30,144,255);
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
		cout << "Player " << player->colorID << " Points: " << player->points << endl;
	}
}

void removePoint(Character *player, Shape *s) 
{
	if (player->colorID == s->boxColorID && s->boxColorID != 0) {
		player->points--;	
		cout << "Player " << player->colorID << " Points: " << player->points << endl;
	}
}

void render(Game *game)
{
	float w, h;
	glClear(GL_COLOR_BUFFER_BIT);

	//renderViewport(0, gl.xres, gl.yres);

	//Draw shapes...
	Shape *s;

	//==============================================
	// Draw Map
	//
	// BOTTOM SCREEN

	// Init map first
    if (initializeFlag) { 
        for (int i = 1; i < totalCubes; i++) {
            glColor3ub(10,255,0);

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
                glColor3ub(30,144,255);
            } else {
                glColor3ub(10,255,0);
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

	// CHARACTER
	//Character *char1;
	//float cx = gl.xres/2.0;
	//float cy = gl.yres/2.0;
	//h = 200.0;
	//w = h * 0.5;
	//
	//char1->cx = gl.xres/2;
	//char1->cy = gl.yres/2;
	//
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, gl.yellowcharTexture);
	//
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
	// Player 1 Draw
	glBegin(GL_QUADS);
	if (gl.keys[XK_Right] || !leftFaceChar1)
	{
		glTexCoord2f(tx + .5, ty + 1); glVertex2i(char1->cx + char1->width, char1->cy - char1->height);
		glTexCoord2f(tx,       ty + 1); glVertex2i(char1->cx - char1->width, char1->cy - char1->height);
		glTexCoord2f(tx,              ty); glVertex2i(char1->cx - char1->width, char1->cy + char1->height);
		glTexCoord2f(tx + .5, ty);        glVertex2i(char1->cx + char1->width, char1->cy + char1->height);
		gl.resultChar1 = 0;	
	}

	if (gl.keys[XK_Left] || leftFaceChar1)
	{
		glTexCoord2f(tx + .5, ty + 1); glVertex2i(char1->cx - char1->width, char1->cy - char1->height);
		glTexCoord2f(tx + .5,        ty); glVertex2i(char1->cx - char1->width, char1->cy + char1->height);
		glTexCoord2f(tx,              ty); glVertex2i(char1->cx + char1->width, char1->cy + char1->height);
		glTexCoord2f(tx, ty + 1);       glVertex2i(char1->cx + char1->width, char1->cy - char1->height);
		gl.resultChar1 = 1;
	}
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_ALPHA_TEST); 	
	
    // Draw BluePortal
    float cx = 40;
    float cy = 400;
    h = 60;
    w = 60;

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, gl.blueportalTexture);
	//
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	ix = gl.blueportalFrame % 2;
	iy = 1;
	if (gl.blueportalFrame >= 2)
		iy = 0;
	tx = (float)ix / 2.0;
	ty = (float)iy / 1.0;

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


	// Player 2    
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, gl.bluecharTexture);
	//
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	ix = gl.bluecharFrame % 2;
	iy = 1;
	if (gl.bluecharFrame >= 2)
		iy = 0;
	tx = (float)ix / 2.0;
	ty = (float)iy / 1.0;

	glBegin(GL_QUADS);
	if (gl.keys[XK_d] || !leftFaceChar2)
	{
		glTexCoord2f(tx + .5, ty + 1); glVertex2i(char2->cx + char2->width, char2->cy - char2->height);
		glTexCoord2f(tx,       ty + 1); glVertex2i(char2->cx - char2->width, char2->cy - char2->height);
		glTexCoord2f(tx,              ty); glVertex2i(char2->cx - char2->width, char2->cy + char2->height);
		glTexCoord2f(tx + .5, ty);        glVertex2i(char2->cx + char2->width, char2->cy + char2->height);
		gl.resultChar2 = 0;	
	}

	if (gl.keys[XK_a] || leftFaceChar2)
	{
		glTexCoord2f(tx + .5, ty + 1); glVertex2i(char2->cx - char2->width, char2->cy - char2->height);
		glTexCoord2f(tx + .5,        ty); glVertex2i(char2->cx - char2->width, char2->cy + char2->height);
		glTexCoord2f(tx,              ty); glVertex2i(char2->cx + char2->width, char2->cy + char2->height);
		glTexCoord2f(tx, ty + 1);       glVertex2i(char2->cx + char2->width, char2->cy - char2->height);
		gl.resultChar2 = 1;
	}


	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_ALPHA_TEST); 	


	drawCircle(30);

	// countdown timer
	countdown();

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



