#include "lexer.h"

double lex_number(std::string::iterator& it)
{
	double value = 0;
	while (isdigit(*it))
	{
		value = value * 10 + (*it - '0');
		++it;
	}
	return value;
}

std::vector<token> lex(std::string formula)
{
	// Appending a space at the end of the formula makes lexing numbers much easier.
	// If you had a string like "123", asking whether the character after the 3
	// is a digit would crash, because there'd simply be no character after the 3.
	formula += ' ';

	std::vector<token> tokens;
	for (auto it = formula.begin(); it != formula.end(); ++it)
	{
		if (!isspace(*it))
		{
			token t = {*it, 0.0};
			if (isdigit(*it))
			{
				t.kind = NUMBER;
				t.value = lex_number(it);
				--it;
			}
			tokens.push_back(t);
		}
	}

	// Having a detectable END token inside the list makes parsing much easier,
	// because then we don't have to pass the end iterator around all the time.
	token END_token = {END, 0.0};
	tokens.push_back(END_token);

	return tokens;
}
