#include "sha2.h"
#include <gpa/input>
#include <map>
#include <vector>
#include <filesystem>
namespace fs = std::tr2::sys;

// Datenstruktur, die für jeden Fingerabdruck eine Liste von Dateipfaden speichert
// ...





void walk_directory(fs::path root)
{
	std::cout << "===> " << root << "\n";
	for (auto it = fs::directory_iterator(root); it != fs::directory_iterator(); ++it)
	{
		if (is_directory(it->status()))
		{
			walk_directory(it->path());
		}
		else
		{
			sha256 fingerprint = sha256_from_file(it->path());
			std::cout << fingerprint << ' ' << it->path() << '\n';
			// Ergänze die Datenstruktur um Fingerabdruck und Dateipfad
			// ...

		}
	}
	std::cout << "<=== " << root << '\n';
}

void print_duplicates()
{
	// ...
}

int main()
{
	walk_directory("pictures");
	print_duplicates();
}
