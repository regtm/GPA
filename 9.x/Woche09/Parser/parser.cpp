#include "parser.h"
#include <iostream>
#include <stdexcept>
#include <string>

struct intermediate_result
{
	iter end;       // Where did the function stop?
	double value;   // What did the function compute?
};

void explain_intermediate_result(const std::string& nonterminal, iter begin, intermediate_result result)
{
	std::cout << nonterminal << ": ";
	for (; begin != result.end; ++begin)
	{
		std::cout << *begin << ' ';
	}
	std::cout << "-> " << result.value << '\n';
}

intermediate_result parse_sum(iter begin);
intermediate_result parse_term(iter begin);
intermediate_result parse_factor(iter begin);

double parse(iter begin)
{
	intermediate_result result = parse_sum(begin);
	if (result.end->kind != END) throw std::runtime_error("unexpected trailing input");

	return result.value;
}

// sum:
//   term { + term }
intermediate_result parse_sum(iter begin)
{
	intermediate_result a = parse_term(begin);
	while ((a.end->kind == '+') || (a.end->kind == '-'))
	{
		intermediate_result b = parse_term(a.end + 1);
		if (a.end->kind == '+')
		{
			a.value += b.value;
		}
		else
		{
			a.value -= b.value;
		}
		a.end = b.end;
	}

	explain_intermediate_result("   sum", begin, a);
	return a;
}

// term:
//   factor { * factor }
intermediate_result parse_term(iter begin)
{
	intermediate_result a = parse_factor(begin);
	while (a.end->kind == '*')
	{
		intermediate_result b = parse_factor(a.end + 1);
		a.value *= b.value;
		a.end = b.end;
	}

	explain_intermediate_result("  term", begin, a);
	return a;
}

// factor:
//   number
//   ( sum )
intermediate_result parse_factor(iter begin)
{
	intermediate_result result;
	if (begin->kind == NUMBER)
	{
		result.end = begin + 1;
		result.value = begin->value;
	}
	else if (begin->kind == '(')
	{
		result = parse_sum(begin + 1);
		if (result.end->kind != ')') throw std::runtime_error("unmatched opening parenthesis");

		++result.end;
	}
	else
	{
		throw std::runtime_error("expected number or opening parenthesis");
	}

	explain_intermediate_result("factor", begin, result);
	return result;
}
