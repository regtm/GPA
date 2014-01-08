#include "lexer.h"
#include "parser.h"
#include <gpa/input>
#include <stdexcept>

void evaluate(const std::string& formula)
{
	try
	{
		std::vector<token> tokens = lex(formula);
		double a = parse(tokens.begin());
		std::cout << a << "\n\n";
	}
	catch (std::runtime_error& ex)
	{
		std::cout << ex.what() << "\n\n";
	}
}

int main()
{
	std::cout << "Please enter formulas like 2*3+5 and I will evaluate them!\n\n";
	std::string formula = gpa::read_string("> ");
	while (!formula.empty())
	{
		evaluate(formula);
		formula = gpa::read_string("> ");
	}
}
