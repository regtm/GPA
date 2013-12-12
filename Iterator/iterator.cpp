#include <vector>
#include <string>
//#include <gpa/input>
#include <iostream>

using namespace std;

void iterieren(int limit)
{
	
	vector<string> abc = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
	
	int end;
	vector<string>::iterator li;

	//Wie werden Variablen verschiedener Typen im gleichen Schleifenrumps initialisiert?
	for (end=0,li = abc.begin(); end != limit; ++li, ++end)
	{
		cout << *li;
	}
	cin.get();
}

int main()
{
	iterieren(10);
}
