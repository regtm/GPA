#pragma once

#include "token.h"
#include <vector>

typedef std::vector<token>::const_iterator iter;

// Parses the sequence of tokens starting at begin until the special END token
// and returns the result of evaluating these tokens as a mathematical expression.
// Example: parse(lex( "2*3+5" ).begin()) -> 11
double parse(iter begin);
// If the sequence of tokens cannot be parsed, a std::runtime_error is thrown.
// Example: parse(lex( "2*(3+5" ).begin()) -> std::runtime_error("unmatched opening parenthesis")
