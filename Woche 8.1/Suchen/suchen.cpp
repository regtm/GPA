#include "suchen.h"
#include <iostream>

iter lineare_suche(iter von, iter bis, int gesuchte_zahl)
{
	for (iter it = von; it != bis; ++it)
	{
		if (*it == gesuchte_zahl) return it;
	}
	return bis;
}

/*
8.1.1
Im günstigsten Fall muss nur das "von" Element untersucht werden.
Im ungünstigsten Fall ist die gesuchte Zahl im letzten Element gespeichert und es müssen "bis - von -1" Elemente untersucht werden, 
sofern gegeben ist, dass die gesuchte Zahl im vector enthalten ist, ansonsten "bis-von".
Im Durchschnitt müssen 50% der Elemente durchsucht werden.
Vorraussetzung für diese Annahmen ist, dass die gesuchte Zahl nur einmal vorhanden ist und auch nur einmal gefunden werden soll.
*/


/*
8.1.2
Bei der binären Suche wird nach jedem Suchschritt die zu untersuchende Menge halbiert. Vorraussetzung ist dabei, dass die Elemente mit einander verglichen werden können.
Bsp: a>b>c>d>e>f>g>h>i   gesucht: h
Der mittlere Wert der List wird nun mit der gesuchten Buchstaben verglichen.
e>h 
-> true (gesuchtes Elemnt im rechten Teil des Baums, der rechte Pointer bleibt gleich, links wird auf "mitte+1" gesetzt.) 
-> false (gesuchtes Element im linken Teil des Baums, der linke Pointer bleibt gleich, rechts wird auf "rechts-1" gesetzt.)
Somit ist die Anzahl der zu durchsuchenden Elemente halbiert und der Vorgang wird so lange wiederholt, bis der gesuchte Buchstabe gefunden ist.
*/

/*
8.1.3
Da sich der Suchbereich in Form von links und rechts verändert wurde, muss nun die neue Mitte des Bereichs gefunden werden, die in diesem Fall der Index 8 ist.
Der Index wird dann durch (links + rechts)/2 errechnet. Was passiert bei ungerader Anzahl?

*/


// Gesuchte Zahl 9999999 führt zu Assertion Error?!

iter binaere_suche(iter von, iter bis, int gesuchte_zahl)
{
	const iter nicht_gefunden = bis;
	
	//iter l = von;
	//iter m = l+(bis-von-1) / 2;
	//iter r = bis;
	
	while (von !=bis)
	{
		iter mitte = von + (bis - von) / 2;
		
		

		if (*mitte > gesuchte_zahl)
		{
			bis = mitte;

		}
		else if (*mitte < gesuchte_zahl)
		{
			von = mitte + 1;
		}
		else
		{
			return mitte;
		}
	}
	
	return nicht_gefunden;
}
