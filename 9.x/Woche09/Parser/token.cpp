#include "token.h"

std::ostream& operator<<(std::ostream& os, token t)
{
	if (t.kind == NUMBER)
	{
		os << t.value;
	}
	else
	{
		os << t.kind;
	}
	return os;
}
