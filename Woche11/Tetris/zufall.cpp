#include "zufall.h"

unsigned int random_seed = 1234567890;

// returns a random word using a linear congruential generator
unsigned int random_word()
{
	random_seed = random_seed * 1664525 + 1013904223;
	return random_seed;
}

// returns a random number between 0 (inclusive) and 1 (exclusive)
double random_double()
{
	return random_word() / 4294967296.0;
}

// returns a random integer between 0 (inclusive) and grenze (exclusive)
int zufallszahl_kleiner_als(int grenze)
{
	return int(grenze * random_double());
}
