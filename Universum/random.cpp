#include "graphics.h"

word random_seed = 1234567890;

// returns a random word using a linear congruential generator
word random_word()
{
	random_seed = random_seed * 1664525 + 1013904223;
	return random_seed;
}

// returns a random number between 0 (inclusive) and 1 (exclusive)
double random_double()
{
	return random_word() / 4294967296.0;
}

// returns a random number between lower (inclusive) and upper (exclusive)
double random_double_between(double lower, double upper)
{
	// Folgendes entspricht noch nicht der Spezifikation,
	// sieht aber immerhin schon ganz nett aus :)
	//return random_double() * upper +(lower*0.5);
	return random_double() * (upper - lower) + lower;
}
