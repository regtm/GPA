#include "graphics.h"
#include "random.h"
#include <vector>
#include <cmath>

const int number_of_bodies = 1000;

std::vector<double> x_positions(number_of_bodies);
std::vector<double> y_positions(number_of_bodies);
std::vector<double> x_velocities(number_of_bodies);
std::vector<double> y_velocities(number_of_bodies);
std::vector<double> masses(number_of_bodies);
std::vector<word>   colors(number_of_bodies);

void initialize()
{
	for (int i = 0; i != number_of_bodies; ++i)
	{
		x_positions[i] = random_double_between(0.1 * SCREEN_WIDTH, 0.9 * SCREEN_WIDTH);
		y_positions[i] = random_double_between(0.1 * SCREEN_HEIGHT, 0.9 * SCREEN_HEIGHT);
		colors[i] = random_word() / 256;
		masses[i] = random_double_between(0.001, 1);
	}
}

void render(word milliseconds_since_start)
{
	for (int i = 0; i != number_of_bodies; ++i)
	{
		blend_aa_pixel(x_positions[i], y_positions[i], colors[i]);
	}
}

double safe_distance_squared(double dx, double dy)
{
	double distance_squared = dx * dx + dy * dy;
	if (distance_squared < 1)
	{
		distance_squared = 1;
	}
	return distance_squared;
}

void update_velocities(double delta_time)
{
	for (int i = 0; i != number_of_bodies; ++i)
	{
		double x_acceleration = 0;
		double y_acceleration = 0;

		for (int k = 0; k != number_of_bodies; ++k)
		{
			double dx = x_positions[k] - x_positions[i];
			double dy = y_positions[k] - y_positions[i];

			double rr = safe_distance_squared(dx, dy);

			/*
			x_acceleration += dx / rr;
			y_acceleration += dy / rr;
			*/

			// beschleunigt die graphische Darstellung um ca. 35fps			
			double kehr_rr = fast_reciprocal(rr);
			double kehr_r = fast_reciprocal_sqrt(rr);
			double kehr_masses = fast_reciprocal(masses[i]);
			x_acceleration += dx * kehr_r * kehr_rr *kehr_masses;
			y_acceleration += dy * kehr_r * kehr_rr *kehr_masses;
			
		}
		x_velocities[i] += x_acceleration * delta_time;
		y_velocities[i] += y_acceleration * delta_time;
	}
}

void update_positions(double delta_time)
{
	for (int i = 0; i != number_of_bodies; ++i)
	{
		x_positions[i] += x_velocities[i] * delta_time;
		y_positions[i] += y_velocities[i] * delta_time;
	}
}

void update(word milliseconds_since_last_update)
{
	double delta_time = milliseconds_since_last_update / 1000.0;

	update_velocities(delta_time);
	update_positions(delta_time);
}
