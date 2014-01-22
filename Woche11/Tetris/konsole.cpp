#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <conio.h>

void verstecke_cursor()
{
	CONSOLE_CURSOR_INFO info = { 1, FALSE };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void platziere_cursor(int x, int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void warte(int millisekunden)
{
	Sleep(millisekunden);
}

int zeitstempel()
{
	return timeGetTime();
}

bool taste_wurde_gedrueckt()
{
	return _kbhit() != 0;
}

int gedrueckte_taste()
{
	return _getch();
}
