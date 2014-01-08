#pragma once

#include "token.h"
#include <string>
#include <vector>

// Converts a string containing a mathematical formula into a list of tokens.
// Example: lex("123+456*789") -> {123, +, 456, *, 789}
std::vector<token> lex(std::string formula);
