#include "primzahlen.h"

std::vector<int> primzahlen_bis(int grenze)
{
	// For some weird reason, std::vector<bool> is incredibly slow,
	// so I chose to use std::vector<char> for the sieve instead.
	std::vector<char> prim(grenze, true);
	std::vector<int> primzahlen;
	for (int i = 2; i < grenze; ++i)
	{
		if (prim[i])
		{
			primzahlen.push_back(i);
			for (int k = 2 * i; k < grenze; k += i)
			{
				prim[k] = false;
			}
		}
	}
	return primzahlen;
}
