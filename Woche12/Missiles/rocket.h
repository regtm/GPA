#pragma once

#include "vector2d.h"
#include "graphics.h"

struct rocket
{
	vector2d origin;
	vector2d target;
	vector2d position;
	int time_of_launch;
	int time_of_arrival;
	int flight_duration;
	word color;
};

rocket make_rocket(double originX, double originY, double targetX, double targetY, double velocity, word color);
bool rocket_is_underway(const rocket& r);
void update_rocket_position(rocket& r);
void draw_rocket(const rocket& r);
