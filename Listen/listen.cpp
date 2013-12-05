#include <gpa/input>
#include <algorithm>
#include <string>
#include <vector>

// Was bedeutet diese Zeile?
std::vector<std::string> read_strings()					// Via read_strings() eingelesene Strings werden in einem Vector
														// also einer Liste gespeichert.
{
	// Was bedeutet diese Zeile?
	std::vector<std::string> strings;					// Ein Vector namens strings wird intialisiert.

	std::string input = gpa::read_string("> ");
	while (!input.empty())
	{
		// Was bedeutet diese Zeile?
		strings.push_back(input);						// An das Ende Vektors strings wird der Wert des Strings input 
														// als neues Element angehängt.

		input = gpa::read_string("> ");
	}
	// Was bedeutet diese Zeile?
	return strings;										// Die Fuktion read_strings() gibt die im String strings
}														// gespeicherten Werte bei Aufruf der Funktion zurück.


void schreibe_per_foreach(std::vector<std::string> strings)
{
	for (std::string s : strings)
	{
		std::cout << s << ' ';
	}
	std::cout << '\n';
}

void schreibe_per_index(std::vector<std::string> strings)
{
	for (int i = 0; i != strings.size(); ++i)
	{
		std::cout << strings[i] << ' ';
	}
	std::cout << '\n';
}

void schreibe_per_iterator(std::vector<std::string> strings)
{
	for (auto it = strings.begin(); it != strings.end(); ++it)
	{
		std::cout << *it << ' ';
	}
	std::cout << '\n';
}


void schreibe_trennlinie()
{
	std::cout << "-------------------------------------------------------------------------------\n";
}

int main()
{
	std::vector<std::string> strings = read_strings();
	schreibe_per_foreach(strings);
	schreibe_trennlinie();

	std::sort(strings.begin(), strings.end());
	schreibe_per_index(strings);
	schreibe_trennlinie();

	while (!strings.empty())
	{
		strings.erase(strings.begin());
		schreibe_per_iterator(strings);
	}
	schreibe_trennlinie();
}
