#include <gpa/input>
#include <vector>
#include <string>
using namespace std;

vector<string> board{ "wayne", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
int played_round = -1;





string ident()
{
	if (played_round % 2 == 0)
	{
		return "X";
	}
	else
	{
		return "O";
	}
}


bool game_over()
{

	string id = ident();


	return
		board[1] == id && board[2] == id && board[3] == id ||
		board[4] == id && board[5] == id && board[6] == id ||
		board[7] == id && board[8] == id && board[9] == id ||
		board[1] == id && board[4] == id && board[7] == id ||
		board[2] == id && board[5] == id && board[8] == id ||
		board[3] == id && board[6] == id && board[9] == id ||
		board[1] == id && board[5] == id && board[9] == id ||
		board[3] == id && board[5] == id && board[7] == id;
		
}

void draw_board()
{
	cout << "\n\n\tTic Tac Toe\n\n";

	cout << "\tX   vs  O " << '\n' << '\n';
	cout << '\n';

	cout << "\t     |     |     " << '\n';
	cout << "\t  " << board[7] << "  |  " << board[8] << "  |  " << board[9] << '\n';

	cout << "\t_____|_____|_____" << '\n';
	cout << "\t     |     |     " << '\n';

	cout << "\t  " << board[4] << "  |  " << board[5] << "  |  " << board[6] << '\n';

	cout << "\t_____|_____|_____" << '\n';
	cout << "\t     |     |     " << '\n';

	cout << "\t  " << board[1] << "  |  " << board[2] << "  |  " << board[3] << '\n';

	cout << "\t     |     |     " << '\n' << '\n';
}

bool istGueltigeEingabe(int zahl)
	{
	return zahl <= 9 && zahl >= 1 && board.at(zahl) != "X" && board.at(zahl) != "O";
	}

int gibGueltigeEingabe()
{
	int input = gpa::read_int("");
	while (!istGueltigeEingabe(input))
	{
		cout << "\tGib bitte eine Zahl zwischen 1 und 9 ein.\n";
		cout << "\t" << ident() << " make your move:";
		input = gpa::read_int("");
	}


	return input;
}

int main()
{
	while (!game_over() && played_round != 8)
	{
		played_round++;
		draw_board();

		cout << "\t" << ident() << " make your move:";
		int move = gibGueltigeEingabe();

		board[move] = ident();



	}
	if (played_round != 8)
	{
		cout << "\tWinner: " << ident();
	}
	else
	{
		cout << "\tDraw";
	}
}
