#pragma once

#include "graphics.h"

const word INITIAL_RANDOM_SEED = 1234567890;

// returns a random word using a linear congruential generator
word random_word();

// returns a random number between 0 (inclusive) and 1 (exclusive)
double random_double();

// returns a random number between lower (inclusive) and upper (exclusive)
double random_double_between(double lower, double upper);

void reset_random_number_generator();
