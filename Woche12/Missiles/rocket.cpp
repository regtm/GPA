#include "rocket.h"

rocket make_rocket(double originX, double originY, double targetX, double targetY, double velocity, word color)
{
	vector2d origin = {originX, originY};
	vector2d target = {targetX, targetY};
	int duration = int(length(target - origin) / velocity * 1000);
	rocket r = {origin, target, origin, current_time, current_time + duration, duration, color};
	return r;
}

bool rocket_is_underway(const rocket& r)
{
	return current_time < r.time_of_arrival;
}

void update_rocket_position(rocket& r)
{
	int elapsed_time = current_time - r.time_of_launch;
	double f = double(elapsed_time) / r.flight_duration;
	if (f < 1)
	{
		r.position = r.origin + (r.target - r.origin) * f;
	}
	else
	{
		r.position = r.target;
	}
}

void draw_rocket(const rocket& r)
{
	draw_aa_line(r.origin.x, r.origin.y, r.position.x, r.position.y, r.color);
}
