#pragma once

struct vector2d
{
	double x;
	double y;
};

vector2d operator+(vector2d a, vector2d b);
vector2d operator-(vector2d a, vector2d b);
vector2d operator*(vector2d a, double b);
double length(vector2d v);
