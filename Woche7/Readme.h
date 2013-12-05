/*
7.1.1
Das Programm zeigt einen Prompt an, in den Der Benutzer beliebige Zeichenfolgen eintragen kann.
Durch betätigen der Return Taste wird die Zeichenfolge abgespeichert und weitere Zeichenfolgen
können eigegeben und gespeichert werden. Die Reihenfolge der Abgeschickten Promptzeilen wird dabei ebenfalls gespeichert.
Durch das abschicken einer leeren Promptzeile via Return wird die Eingabephase des Programm beendet.

Bei der nun folgenden Ausgabe werden zuerst die eingegebene Zeilen durch Leerzeichen getrennt dargestellt.
In der durch Trenstriche abgetrennten Zeile werden die einzelnen Eingabezeilen Alphanumerisch aufsteigend sortiert.
Anschließend werden die alphanumerisch aufsteigend sortierten Eingabezeilen immer um die zuvor erste Eingabe 
reduziert ausgegeben.
*/

/*
7.1.2

void schreibe_per_foreach(std::vector<std::string> strings)
{
for (std::string s : strings)
{
std::cout << s << ' ';
}
std::cout << '\n';
}


Welche Bedeutung hat die Syntax for (Typ x : Liste)?
>	

Welchen Typ muss man hier konkret einsetzen?
>	Den entsprechenende Typ der Listenelemente.

Kann man anstelle des Typs auch auto verwenden?
>	Ja, sofern der Compiler c++11 unterstützt und die Liste mit Typ initialisiert wurde.	

---------------------------------------------------------------------------------------

void schreibe_per_index(std::vector<std::string> strings)
{
for (int i = 0; i != strings.size(); ++i)
{
std::cout << strings[i] << ' ';
}
std::cout << '\n';
}


Welchen Typ hat der Ausdruck strings[i]?
>	string bzw. std::string
	

Welchen Wert hat i bei der letzten Ausführung des Schleifenrumpfs?
>	string.size() -1	

Welchen Typ hat i, wenn man auto i=0; schreibt?
>	Sollte eigentlich einen Fehler produzieren, da sich auto auf keine Initialisierung beziehen kann, funktioniert
	merkwürdiger Weise aber trotzdem.



--------------------------------------------------------------------------

void schreibe_per_iterator(std::vector<std::string> strings)
{
for (auto it = strings.begin(); it != strings.end(); ++it)
{
std::cout << *it << ' ';
}
std::cout << '\n';
}


Welchen Typ hat die Variable it?
>	string bzw. std::string

Auf welches Element zeigt strings.end()?
>	Auf ein leeres Element am Ende des Vektors.

Welchen Typ hat der Ausdruck *it?
>	*it gibt den Inhalt der Adresse it aus, daher ist der Typ string.

Was ist das Ergebnis von *it?
>	Den Wert der an der Adresse auf die it zeigt gespeichert ist.	

Was bewirkt der Ausdruck ++it?
>	Der Iterator rückt eine Adresse weiter.

*/