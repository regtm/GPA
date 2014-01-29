#include "random.h"
#include <Windows.h>

word random_seed = timeGetTime();

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
	return (upper - lower) * random_double() + lower;
}
