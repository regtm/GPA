#include <gpa/input>
#include <vector>
#include <string>
using namespace std;

vector<string> board{"7","8","9","4","5","6","1","2","3"};
int played_round = 0;

string ident()
{
	if (played_round % 2 != 0)
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

	if (
		board[0] == id && board[1] == id && board[2] == id ||
		board[3] == id && board[4] == id && board[5] == id ||
		board[6] == id && board[7] == id && board[8] == id ||
		board[0] == id && board[3] == id && board[6] == id ||
		board[1] == id && board[4] == id && board[7] == id ||
		board[2] == id && board[5] == id && board[8] == id ||
		board[0] == id && board[4] == id && board[8] == id ||
		board[2] == id && board[4] == id && board[6] == id
		)
	{
		return true;
	}
	else {
		return false;
	}
}

void draw_board()
{
	cout << "\n\n\tTic Tac Toe\n\n";

	cout << "\tX   vs  O " << '\n' << '\n';
	cout << '\n';

	cout << "\t     |     |     " << '\n';
	cout << "\t  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << '\n';

	cout << "\t_____|_____|_____" << '\n';
	cout << "\t     |     |     " << '\n';

	cout << "\t  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << '\n';

	cout << "\t_____|_____|_____" << '\n';
	cout << "\t     |     |     " << '\n';

	cout << "\t  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << '\n';

	cout << "\t     |     |     " << '\n' << '\n';
}

int main()
{
	while (!game_over() && played_round != 9)
	{
		draw_board();

		played_round++;


		cout << "\t" << ident() << " make your move:";
		int move = gpa::read_int("");


		auto it = board.begin();


		if (board.at(move) != "X" && board.at(move) != "O")
		{
			board.erase(it + move);
			board.insert(it + move, ident());
		}
		else{
			cout << "\tInvalid move!";
		}

			draw_board();

	}
	if (played_round != 9)
	{
		cout << "\tWinner: " << ident();
	}
	else
	{
		cout << "\tDraw";
	}
}
