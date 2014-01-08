#pragma once

//
// based on TinyPTC by Glenn Fiedler
// http://sourceforge.net/projects/tinyptc/
//

// integer types
typedef unsigned int   word;
typedef unsigned short half;
typedef unsigned char  byte;

// tinyptc api
int ptc_open(const char * title, int width, int height);
void ptc_close();

// configuration
#define __PTC_WINDOWED__
#define __PTC_CENTER_WINDOW__
#define __PTC_RESIZE_WINDOW__
#define __PTC_SYSTEM_MENU__
#define __PTC_ICON__ "IDI_MAIN"
#define __PTC_ALLOW_CLOSE__
#define __PTC_DISABLE_SCREENSAVER__



// GPA additions

const double PI = 3.141592653589793;

const word SCREEN_WIDTH = 800;
const word SCREEN_HEIGHT = 600;
const word SCREEN_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT;

void clear_screen();

void draw_pixel(word x, word y, word color);
void blend_pixel(word x, word y, word color);
void blend_aa_pixel(double x, double y, word color);
void draw_aa_line(double x0, double y0, double x1, double y1, word color);

// approximates 1/x with 11 bits of precision
double fast_reciprocal(double x);

// approximates 1/sqrt(x) with 11 bits of precision
double fast_reciprocal_sqrt(double x);

void repaint(int delay_ms);
