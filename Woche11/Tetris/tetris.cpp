#include "konsole.h"
#include "zufall.h"
#include <gpa/input>
#include <vector>
#include <map>
using namespace std;

/* 
UP_ARROW 72
LEFT_ARROW 75
RIGHT_ARROW 77
DOWN_ARROW 80
SQUARE 254

board scheme
1,2,3,4,5,6,7...
11,12,13,14...
21,22,23,24...
*/

int height = 20;
int width = 10;
int tile = 2;

map <int, int> board;

void draw_board()
{

	unsigned char vertical_pipe = 186;
	unsigned char horizontal_pipe = 205;
	unsigned char corner_l = 200;
	unsigned char corner_r = 188;

	cout << "\t -=-=-=- Tetris -=-=-=-" << "\n\n";
	for (int i = 0; i <= height*tile; ++i)
	{
		cout << "\t" << vertical_pipe;
		for (int i2 = 0; i2 <= width*tile; ++i2)
		{
			cout << " ";
		}
		cout << vertical_pipe << "\n";
	}
	cout << "\t" << corner_l;
	for (int i3 = 0; i3 <= width*tile; ++i3)
	{
		cout << horizontal_pipe;
	}
	cout << corner_r;
}

void create_map(int height,int width)
{
	for (int i = 0; i <= height*width; ++i)
	{
		board[i] = 0;
	}
}

int check_collision(int first, int sec, int third, int fourth)
{
	int check = 0; //0 == no collision, 1 == hit another block, 2 == hit end of the board
	
	// check if hit another block
	if (board[first + 10] == 0 && board[sec + 10] == 0 && board[third + 10] == 0 && board[fourth + 10] == 0)
	{
		check = 1;
	}


	//check for end of the board
	if (first + 10 > 200 || sec + 10 > 200 || third + 10 > 200 || fourth + 10 > 200 || )
	{
		check = 2;
	}
	
}

void setblock(int first, int sec, int third, int fourth)
{
	check_collision(first, sec, third, fourth);

}

void init_block()
{
	int random_start = zufallszahl_kleiner_als(21);
	int random_block = zufallszahl_kleiner_als(6); // 1 square, 2 triangle, 3 long, 4 L, 5 reverse L
	int random_direction = zufallszahl_kleiner_als(5);
	
	switch (random_block)
	{
	case 1: // square
		setblock(random_start, random_start + 1, random_start + 10, random_start + 11);
		break;
	case 2: // triangle
		setblock(random_start, random_start + 1, random_start + 2, random_start + 11);
		break;
	case 3: // long
		setblock(random_start, random_start + 10, random_start + 20, random_start + 30);
		break;
	case 4: // L
		setblock(random_start, random_start + 10, random_start + 20, random_start + 21);
		break;
	case 5: // reverse L
		setblock(random_start, random_start + 10, random_start + 20, random_start + 19);
		break;
	}
}

bool game_over()
{
	return true;
}




void init()
{
	draw_board();
	create_map();
}

int play(int speed)
{
	return 1;
}

void fin(int score)
{
	cout << "You reached" << score << "points!";
}

int main()
{
	init();
	int start = zeitstempel();
}
