#pragma once

#include "graphics.h"

// returns a random word using a linear congruential generator
word random_word();

// returns a random number between 0 (inclusive) and 1 (exclusive)
double random_double();

// returns a random number between lower (inclusive) and upper (exclusive)
double random_double_between(double lower, double upper);
