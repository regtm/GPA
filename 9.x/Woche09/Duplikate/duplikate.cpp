#include "sha2.h"
#include <gpa/input>
#include <map>
#include <vector>
#include <filesystem>
namespace fs = std::tr2::sys;


// 9.1
//	Die Wahrscheinichkeit für eine Kollision beträgt (1/2)^256

// Datenstruktur, die für jeden Fingerabdruck eine Liste von Dateipfaden speichert
// ...
std::map<sha256, std::vector<fs::path> > maptype; 

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
			
			if (maptype.count(fingerprint) != 0)
			{
				maptype.find(fingerprint)->second.push_back(it->path()); 
			}
			else 
			{
				std::vector<fs::path> path;
				path.push_back(it->path()); 
				maptype.insert(std::pair<sha256, std::vector<fs::path>>(fingerprint, path)); 
			}
			std::cout << fingerprint << '>>' << it->path() << '\n'; 
			
		}
	}
	std::cout << "<=== " << root << '\n';
}

void print_duplicates()
{
	for (auto it = maptype.begin(); it != maptype.end(); it++) 
	{
		if (it->second.size() > 1) 
		{
			std::cout << "fingerprint" << it->first << "\n";
			
			for (auto path : it->second)
			{
				std::cout << path << "\n";
			}
		}
	}
}

int main()
{
	walk_directory("pictures");
	print_duplicates();
}

