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


map <int, int> board;

void draw_board(vector<int> active_block)
{

	platziere_cursor(0, 0);

	unsigned char vertical_pipe = 186;
	unsigned char horizontal_pipe = 205;
	unsigned char corner_l = 200;
	unsigned char corner_r = 188;
	unsigned char block = 219;
	unsigned char leer = 32;

	int blocks = 1;

		cout << "\t -=-=-=- Tetris -=-=-=-" << "\n\n";
		for (int i = 1; i <= height; ++i)
		{
			cout << "\t" << vertical_pipe;
			for (int i2 = 1; i2 <= width; ++i2)
			{
				
				if (blocks == active_block[0] || blocks == active_block[1] || blocks == active_block[2] || blocks == active_block[3] ||
					board[blocks] == 2)
				{
					cout << block;
					
				}
				else
				{
					cout << leer;
					
				}
				++blocks;
				
			}
			cout << vertical_pipe << "\n";
		
		}
		cout << "\t" << corner_l;
		for (int i3 = 1; i3 <= width; ++i3)
		{
			cout << horizontal_pipe;
		}
		cout << corner_r;
	
}

void create_map(int height,int width)
{
	for (int i = 1; i <= height*width; ++i)
	{
		board[i] = 0;
	}
}

int check_collision(vector<int> active_block)
{
	int check = 0; //0 == no collision, 1 == hit another block, 2 == hit end of the board
	
	// check if hit another block
	if (board[active_block[0] + 10] == 0 && board[active_block[1] + 10] == 0 && board[active_block[2] + 10] == 0 && board[active_block[3] + 10] == 0)
	{
		check = 1;
	}


	//check for end of the board
	if (active_block[0] + 10 > 200 || active_block[1] + 10 > 200 || active_block[2] + 10 > 200 || active_block[3] + 10 > 200)
	{
		check = 2;
	}

	return check;
	
}

vector<int> setblock(vector<int> active_block)
{
	if (check_collision(active_block) !=0)
	{
		board[active_block[0]] = 2;
		board[active_block[1]] = 2;
		board[active_block[2]] = 2;
		board[active_block[3]] = 2;
	}

		draw_board(active_block);
		board[active_block[0]] = 1;
		board[active_block[1]] = 1;
		board[active_block[2]] = 1;
		board[active_block[3]] = 1;
	

		return active_block;

}

void deleteblock(vector<int> active_block)
{
	board[active_block[0]] = 0;
	board[active_block[1]] = 0;
	board[active_block[2]] = 0;
	board[active_block[3]] = 0;
}

vector<int> init_block()
{
	int random_start = zufallszahl_kleiner_als(9)+1;
	int random_block = zufallszahl_kleiner_als(5)+1; // 1 square, 2 triangle, 3 long, 4 L, 5 reverse L
	int random_direction = zufallszahl_kleiner_als(4)+1;
	
	vector<int> active_block;


	switch (random_block)
	{
	case 1: // square
		active_block = { random_start, random_start + 1, random_start + 10, random_start + 11 };
		setblock(active_block);
		break;
	case 2: // triangle
		active_block = { random_start, random_start + 1, random_start + 2, random_start + 11 };
		setblock(active_block);
		break;
	case 3: // long
		active_block = {random_start, random_start + 10, random_start + 20, random_start + 30 };
		setblock(active_block);
		break;
	case 4: // L
		active_block = { random_start, random_start + 10, random_start + 20, random_start + 21 };
		break;
	case 5: // reverse L
		active_block = {random_start, random_start + 10, random_start + 20, random_start + 19 };
		setblock(active_block);
		break;
	}

	return active_block;

}



vector<int> gravitation(vector<int> active_block)
{

		deleteblock(active_block);
		active_block = { active_block[0] + 10, active_block[1] + 10, active_block[2] + 10, active_block[3] + 10 };
		active_block = setblock(active_block);
	
	return active_block;
}

int x;

bool game_over()
{
	if (x < 10)
	{
		++x;
		return false;
	}
	else
	{
		return true;
	}
}

void init()
{
	vector<int> active_block = { 0, 0, 0, 0 };
	draw_board(active_block);
	create_map(height,width);
}

int play(int speed)
{
	vector<int> active_block;
		active_block = init_block();
		int x = 0;
		while (x < 10)
		{
			++x;
			while (check_collision(active_block) == 0)
			{
				active_block = gravitation(active_block);
				draw_board(active_block);
			}
			active_block = init_block();
		}
		
	
	
	return 1;
}

void fin(int score)
{
	cout << "You reached" << score << "points!";
}

int main()
{
	
	init();
	int start_input = gedrueckte_taste();
	if (start_input == 115)
	{
		int start = zeitstempel();
		play(1);
	}
	
}
