#include "vector2d.h"
#include <math.h>

vector2d operator+(vector2d a, vector2d b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

vector2d operator-(vector2d a, vector2d b)
{
	a.x -= b.x;
	a.y -= b.y;
	return a;
}

vector2d operator*(vector2d a, double b)
{
	a.x *= b;
	a.y *= b;
	return a;
}

double length(vector2d v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}
