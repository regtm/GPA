#pragma once

#include "graphics.h"

// After drawing a line, the program pauses for a given amount of time.
// Negative values make the program pause until a key is pressed.
// If you don't want any pauses, set the value to 0, but then you have to
// CALL THE repaint FUNCTION MANUALLY WHEN YOU ARE DONE DRAWING.
const int TURTLE_DELAY_MS = 100;

struct turtle
{
	double x;
	double y;
	double angle;
};

// Creates a new turtle that is /distance/ away in t's direction
turtle operator+(turtle t, double distance);

// Creates a new turtle that is rotated left by /angle/
turtle operator<<(turtle t, double angle);

// Creates a new turtle that is rotated right by /angle/
turtle operator>>(turtle t, double angle);

// Draws a line between the two turtles.
// The directions they face have no influence.
void draw_line(const turtle& a, const turtle& b, word color);

// Converts degrees (0..360) to radians (0..2pi)
double radians(double degrees);
