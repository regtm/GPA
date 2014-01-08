#pragma once

#include <ostream>

// Tokens are the "atoms" of parsing. There are four different kinds of tokens:
//  numbers (denoted by the character #)
//  operators (denoted by the characters + - * et cetera)
//  parentheses (denoted by the ( and ) characters)
//  a special END marker (denoted by the character @)
// The value field is only used for the number tokens.
struct token
{
	char kind;
	double value;
};

const char NUMBER = '#';
const char END = '@';

std::ostream& operator<<(std::ostream& os, token t);
