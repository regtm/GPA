#pragma once

#include <vector>

typedef std::vector<int>::iterator iter;

/*
Sucht eine Zahl in einem Bereich und gibt einen Iterator darauf zurück.
Taucht die gesuchte Zahl nicht in dem Bereich auf, wird /bis/ zurückgegeben.
Komplexität: Linear
*/
iter lineare_suche(iter von, iter bis, int gesuchte_zahl);

/*
Sucht eine Zahl in einem aufsteigend geordneten Bereich und gibt einen Iterator darauf zurück.
Taucht die gesuchte Zahl nicht in dem Bereich auf, wird /bis/ zurückgegeben.
Komplexität: Logarithmisch
*/
iter binaere_suche(iter von, iter bis, int gesuchte_zahl);
