#include <gpa/input>
#include <string>
#include <vector>

using namespace std;

// Schreibt eine Zahlenfolge im Format {2, 3, 5, 7} auf die Konsole.
void schreibe_zahlenfolge(std::vector<int> zahlenfolge)
{
	for (auto it = zahlenfolge.begin(); it != zahlenfolge.end(); ++it)
	{
		cout << *it;
		if (it < zahlenfolge.end() - 1)
		{
			cout << ",";
		}
	}
}

// Berechnet die Primfaktoren einer Zahl und gibt sie als Liste zurück.
// Beispiel: berechne_primfaktoren(140) -> {2, 2, 5, 7}
// Hinweis: Die Musterlösung zu schreibe_primfaktoren befindet sich unterhalb von main.
std::vector<int> berechne_primfaktoren(int x)
{
	std::vector<int> faktoren;
	vector<int> bis1000 = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,
		47,53,59,61,67,71,73,79,83,89,97,101,103,107,
		109,113,127,131,137,139,149,151,157,163,167,173,179,181,
		191,193,197,199,211,223,227,229,233,239,241,251,257,263,
		269,271,277,281,283,293,307,311,313,317,331,337,347,349,
		353,359,367,373,379,383,389,397,401,409,419,421,431,433,
		439,443,449,457,461,463,467,479,487,491,499,503,509,521,
		523,541,547,557,563,569,571,577,587,593,599,601,607,613,
		617,619,631,641,643,647,653,659,661,673,677,683,691,701,
		709,719,727,733,739,743,751,757,761,769,773,787,797,809,
		811,821,823,827,829,839,853,857,859,863,877,881,883,887,
		907,911,919,929,937,941,947,953,967,971,977,983,991,997};
	

	for (int prime : bis1000)
	{
		while (x%prime == 0)
		{
			faktoren.push_back(prime);
			x = x / prime;
		}
	}
	if (x > 1)
	{
		faktoren.push_back(x);
	}

	return faktoren;
}

// Berechnet die ersten n Fibonacci-Zahlen und gibt sie als Liste zurück.
// Eine Fibonacci-Zahl ist die Summe ihrer beiden Vorgänger.
// Die ersten beiden Fibonacci-Zahlen seien per Definition 0 und 1.
// Beispiel: berechne_fibonacci_folge(10) -> {0, 1, 1, 2, 3, 5, 8, 13, 21, 34}
std::vector<int> berechne_fibonacci_folge(int n)
{
	vector<int> fib = {0, 1 };
	
	if (n == 0)
	{
		cout << "0?";
	}
	else if (n==1)
	{
		fib = { 0};
	}
	else
	{
		for (int i = 0; i < n-2; ++i)
		{
			int onacci = fib[i] + fib[i + 1];
			fib.push_back(onacci);
		}
	}
	return fib;
}

int main()
{
	schreibe_zahlenfolge({4, 8, 15, 16, 23, 42});

	cout << "\n-------------------------------------------------------------------\n";

	schreibe_zahlenfolge(berechne_primfaktoren(2180));
	
	cout << "\n-------------------------------------------------------------------\n";

	schreibe_zahlenfolge(berechne_fibonacci_folge(10));
}

// Diese Musterlösung kann als Orientierung für berechne_primfaktoren dienen ;)
void schreibe_primfaktoren(int x)
{
	for (int prime : {2, 3, 5, 7})
	{
		while (x % prime == 0)
		{
			std::cout << prime << ' ';
			x /= prime;
		}
	}
	if (x > 1)
	{
		std::cout << x;
	}
	std::cout << '\n';
}
