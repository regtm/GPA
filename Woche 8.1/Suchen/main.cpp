#include "primzahlen.h"
#include "suchen.h"
#include <gpa/input>

const int GRENZE = 10000000;

std::vector<int> berechne_primzahlen()
{
	std::cout << "Bitte warten, Liste der Primzahlen unter " << GRENZE << " wird generiert... ";
	std::vector<int> primzahlen = primzahlen_bis(GRENZE);
	std::cout << "fertig!\n\n";
	return primzahlen;
}

void schreibe_anleitung()
{
	std::cout << "Geben sie Zahlen zwischen 1 und " << GRENZE << " ein.\n";
	std::cout << "Mit der Eingabe 0 beenden Sie das Programm.\n\n";
}

void suche_eingaben_in(iter von, iter bis)
{
	int zahl = gpa::read_int("> ");
	while (zahl != 0)
	{
		//iter it = lineare_suche(von, bis, zahl);
		iter it = binaere_suche(von, bis, zahl);
		if (it == bis)
		{
			std::cout << zahl << " gehoert nicht zu den ersten " << GRENZE << " Primzahlen.\n\n";
		}
		else
		{
			int index = it - von;
			std::cout << zahl << " ist die " << index + 1 << "te Primzahl.\n\n";
		}
		zahl = gpa::read_int("> ");
	}
}

int main()
{
	std::vector<int> primzahlen = berechne_primzahlen();
	schreibe_anleitung();
	suche_eingaben_in(primzahlen.begin(), primzahlen.end());
}
