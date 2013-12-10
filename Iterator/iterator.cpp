#include <vector>
#include <string>
//#include <gpa/input>
#include <iostream>

using namespace std;

void iterieren(int limit)
{
	
	vector<string> abc = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
	
for (vector<string>::iterator li = abc.begin(); li != limit  ; li++)
	{
		cout << *li;
	}
	cin.get();
}

int main()
{
	iterieren(10);
}
