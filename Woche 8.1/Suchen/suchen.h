#pragma once

#include <vector>

typedef std::vector<int>::iterator iter;

/*
Sucht eine Zahl in einem Bereich und gibt einen Iterator darauf zur�ck.
Taucht die gesuchte Zahl nicht in dem Bereich auf, wird /bis/ zur�ckgegeben.
Komplexit�t: Linear
*/
iter lineare_suche(iter von, iter bis, int gesuchte_zahl);

/*
Sucht eine Zahl in einem aufsteigend geordneten Bereich und gibt einen Iterator darauf zur�ck.
Taucht die gesuchte Zahl nicht in dem Bereich auf, wird /bis/ zur�ckgegeben.
Komplexit�t: Logarithmisch
*/
iter binaere_suche(iter von, iter bis, int gesuchte_zahl);
