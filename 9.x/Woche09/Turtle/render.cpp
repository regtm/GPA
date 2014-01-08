#include "random.h"
#include "turtle.h"
#include <cmath>

void draw_pyramid(turtle t, double length)
{
	if (length > 5)
	{
		turtle u = (t + length) << radians(120);
		draw_line(t, u, 0xffff7f);
		draw_pyramid(u, length * 0.9);
	}
}

void render()
{
	turtle base = {200, 400, radians(90)};
	draw_pyramid(base, 400);
}
