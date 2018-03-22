
//===============================================
// Created By:
//      Rodrigo Garcia-Novoa
//
// Frameworks By:
//      Gordon Griesel
//===============================================


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <cstring>
#include <math.h>
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
const float gravity = -0.2f;
//const int MAX_PARTICLES = 10000;
#define ALPHA 1


//===============================================
// Global Instance
// ==============================================
Timers timers;
Global gl;
Character *char1;
Game game;
Shape *s;
    bool leftFace = 0; 
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
void initXWindows(void);
int main(void);
void init_opengl(void);
void cleanupXWindows(void);
void check_mouse(XEvent *e, Game *game);
void check_keys(XEvent *e);
void physics(Game *game);
void render(Game *game);

// ==============================================
// Functions
// ==============================================



// ==============================================

// ==============================================
// Ppm Images
// ==============================================



// ==============================================


int main(void)
{
	srand(time(NULL));
	initXWindows();
	init_opengl();
	//declare game object
	//Game game;

	//declare a box shape
	//game.box[0].width = 300;
	//game.box[0].height = 10;
	//game.box.center.x = 250 + 5*65;
	//game.box.center.y = 600 - 5*60;
	//game.box[0].center.x = gl.xres/2;
	//game.box[0].center.y = 150;

	for (int i = 1; i < 48; i++) {
	    game.box[i].width = 25;
	    game.box[i].height = 25;
	    game.box[i].center.x = 25*i + 40;
	    game.box[i].center.y = 60;
	}
	int total = 1;
	for (int i = 48; i < 95; i++) {
	    game.box[i].width = 25;
	    game.box[i].height = 25;
	    game.box[i].center.x = 25*total + 40;
	    game.box[i].center.y = gl.yres-60;
	}
	total = 1;
	for (int i = 95; i < 119; i++) {
	    game.box[i].width = 25;
	    game.box[i].height = 25;
	    game.box[i].center.x = 65;
	    game.box[i].center.y = 25*total+60;
	}
	total = 1;
	for (int i = 119; i < 143; i++) {
	    game.box[i].width = 25;
	    game.box[i].height = 25;
	    game.box[i].center.x = gl.xres-65;
	    game.box[i].center.y = 25*total+60;
	}

	//start animation
	while (!gl.done) {
		while (XPending(dpy)) {
			XEvent e;
			XNextEvent(dpy, &e);
			check_mouse(&e, &game);
			check_keys(&e);
		}
		physics(&game);
		render(&game);
		glXSwapBuffers(dpy, win);
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

void initXWindows(void)
{
	//do not change
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	int w=WINDOW_WIDTH, h=WINDOW_HEIGHT;
	dpy = XOpenDisplay(NULL);
	if (dpy == NULL) {
		std::cout << "\n\tcannot connect to X server\n" << std::endl;
		exit(EXIT_FAILURE);
	}
	Window root = DefaultRootWindow(dpy);
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
	win = XCreateWindow(dpy, root, 0, 0, w, h, 0, vi->depth,
		InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
	set_title();
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
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
	//==============================================


	//==============================================
	// Get Images
	//==============================================
	gl.mainchar1Image = ppm6GetImage("./images/mainChar1.ppm");	
	//==============================================
	

	//==============================================
	// Generate Textures
	//==============================================
	glGenTextures(1, &gl.mchar1Texture);	
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
	case XK_w:
		timers.recordTime(&timers.maincharacterTime);
		gl.walk ^= 1;
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

void physics(Game *game)
{
	//Particle *p;
/*
	if (game->n <= 0)
		return;

	for (int i = 0; i < game->n; i++)
	{
    		char1 = &game->player[0];
		//p = &game->particle[i];
		char1->vel.y -= GRAVITY;
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

    char1 = &game->player[0];
    char1->cy -= 1;
    
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
    for (int j = 1; j < 48; j++) {
	s = &game->box[j];
	printf("Value char1 cx: %f\n", char1->cx);
	printf("Value char1 cy: %f\n", char1->cy);
	printf("Value index 15: center is %f\n", game->box[15].center.y);
	printf("Value index 15: height is %f\n", game->box[15].height);
	if (char1->cy < (char1->height-5) + s->center.y + s->height) {		// checks top
	    char1->cy = char1->height-10 + s->center.y + s->height;
		printf("COLLISION\n");
	    
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
    }
/*
    printf("Value char1 cy: %f\n", char1->cy);
    printf("Value char1 height: %f\n", char1->height);
    printf("Value center box: %f\n", game->box[15].center.y);
    printf("Value box height: %f\n", game->box[15].height);
*/
    if (gl.walk || gl.keys[XK_Right]) {
	leftFace = 0;
	//man is walking...
	//when time is up, advance the frame.
	timers.recordTime(&timers.timeCurrent);
	double timeSpan = timers.timeDiff(&timers.maincharacterTime, &timers.timeCurrent);
	if (timeSpan > gl.delay) {
	    //advance
	    ++gl.mcharFrame;
	    if (gl.mcharFrame >= 8)
		gl.mcharFrame -= 8;
	    timers.recordTime(&timers.maincharacterTime);
	}
    }

    if (gl.walk || gl.keys[XK_Left]) {
	leftFace = 1;
	//man is walking...
	//when time is up, advance the frame.
	timers.recordTime(&timers.timeCurrent);
	double timeSpan = timers.timeDiff(&timers.maincharacterTime, &timers.timeCurrent);
	if (timeSpan > gl.delay) {
	    //advance
	    ++gl.mcharFrame;
	    if (gl.mcharFrame >= 8)
		gl.mcharFrame -= 8;
	    timers.recordTime(&timers.maincharacterTime);
	}
    }
    
    if (gl.keys[XK_Right]) 
	char1->cx += 8;
    if (gl.keys[XK_Left]) 
    	char1->cx += -8;
    if (gl.keys[XK_Up]) 
    	char1->cy += 8;
    if (gl.keys[XK_Down]) 
    	char1->cy += -8;
}

void render(Game *game)
{
	float w, h;
	glClear(GL_COLOR_BUFFER_BIT);
	//Draw shapes...

	Shape *s;
	//==============================================
	// Draw Map
	//
	// BOTTOM SCREEN
	for (int i = 1; i < 24; i++) {
	    glColor3ub(10,0,250);
	    s = &game->box[i];
	    if (i == 7)
		glColor3ub(0, 255, 0);
	    if (i == 23)
		glColor3ub(255, 0, 0);
	    glPushMatrix();
	    s[i].center.x = 50*i + 40;
	    s[i].center.y = 60;
	    glTranslatef(s[i].center.x, s[i].center.y, s[i].center.z);
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
	/*int total = 1;
	// TOP SCREEN
	for (int i = 48; i < 95; i++) {
	    glColor3ub(10,0,250);
	    if (i == 94)
		glColor3ub(255, 0, 0);
	    //s = &game->box[i];
	    glPushMatrix();
	    s = &game->box[i];
	    s[i].center.x = 25*total + 40;
	    s[i].center.y = gl.yres-60;
	    glTranslatef((25*total)+40, gl.yres-60, s->center.z);
	    w = 25;
	    h = 25;
	    glBegin(GL_QUADS);
	    glVertex2i(-w, -h);
	    glVertex2i(-w, h);
	    glVertex2i( w, h);
	    glVertex2i( w, -h);
	    glEnd();
	    glPopMatrix();
	    total++;
	}
	total = 1;
	// LEFT SCREEN
	for (int i = 95; i < 119; i++) {
	    glColor3ub(10,0,250);
	    if (i == 95)
		glColor3ub(255, 0, 0);
	    if (i == 118)
		glColor3ub(255, 255, 0);
	    //s = &game->box[i];
	    glPushMatrix();
	    s = &game->box[i];
	    s[i].center.x = 65;
	    s[i].center.y = 25*total+60;
	    glTranslatef(65, (25*total)+60, s->center.z);
	    w = 25;
	    h = 25;
	    glBegin(GL_QUADS);
	    glVertex2i(-w, -h);
	    glVertex2i(-w, h);
	    glVertex2i( w, h);
	    glVertex2i( w, -h);
	    glEnd();
	    glPopMatrix();
	    total++;
	}
	total = 1;
	// RIGHT SCREEN
	for (int i = 119; i < 143; i++) {
	    glColor3ub(10,0,250);
	    if (i == 119)
		glColor3ub(255, 0, 155);
	    if (i == 142)
		glColor3ub(255, 55, 0);
	    //s = &game->box[i];
	    glPushMatrix();
	    s = &game->box[i];
	    s[i].center.x = gl.xres-65;
	    s[i].center.y = 25*total+60;
	    glTranslatef(gl.xres-65, (25*total)+60, s->center.z);
	    w = 25;
	    h = 25;
	    glBegin(GL_QUADS);
	    glVertex2i(-w, -h);
	    glVertex2i(-w, h);
	    glVertex2i( w, h);
	    glVertex2i( w, -h);
	    glEnd();
	    glPopMatrix();
	    total++;
	}
	//==============================================
*/

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
	glBindTexture(GL_TEXTURE_2D, gl.mchar1Texture);
	//
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	int ix = gl.mcharFrame % 4;
	int iy = 3;
	if (gl.mcharFrame >= 4)
	    iy = 0;
	float tx = (float)ix / 4.0;
	float ty = (float)iy / 3.0;

	//int result;
	glBegin(GL_QUADS);
	if (gl.keys[XK_Right] || !leftFace)
	{
	    glTexCoord2f(tx + .25, ty + .333); glVertex2i(char1->cx + char1->width, char1->cy - char1->height);
	    glTexCoord2f(tx,       ty + .333); glVertex2i(char1->cx - char1->width, char1->cy - char1->height);
	    glTexCoord2f(tx,              ty); glVertex2i(char1->cx - char1->width, char1->cy + char1->height);
	    glTexCoord2f(tx + .25, ty);        glVertex2i(char1->cx + char1->width, char1->cy + char1->height);
	    gl.result = 0;	
	}

	if (gl.keys[XK_Left] || leftFace)
	{
	    glTexCoord2f(tx + .25, ty + .333); glVertex2i(char1->cx - char1->width, char1->cy - char1->height);
	    glTexCoord2f(tx + .25,        ty); glVertex2i(char1->cx - char1->width, char1->cy + char1->height);
	    glTexCoord2f(tx,              ty); glVertex2i(char1->cx + char1->width, char1->cy + char1->height);
	    glTexCoord2f(tx, ty + .333);       glVertex2i(char1->cx + char1->width, char1->cy - char1->height);
	    gl.result = 1;
	}

	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_ALPHA_TEST); 	
}



