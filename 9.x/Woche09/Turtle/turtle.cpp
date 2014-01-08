#include "turtle.h"
#include <cmath>

turtle operator+(turtle t, double distance)
{
	t.x += sin(t.angle) * distance;
	t.y -= cos(t.angle) * distance;
	return t;
}

turtle operator<<(turtle t, double angle)
{
	t.angle -= angle;
	return t;
}

turtle operator>>(turtle t, double angle)
{
	t.angle += angle;
	return t;
}

void draw_line(const turtle& a, const turtle& b, word color)
{
	draw_aa_line(a.x, a.y, b.x, b.y, color);
	if (TURTLE_DELAY_MS != 0)
	{
		repaint(TURTLE_DELAY_MS);
	}
}

double radians(double degrees)
{
	return degrees * (PI / 180);
}
