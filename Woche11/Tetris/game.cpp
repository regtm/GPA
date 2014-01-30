#include "konsole.h"
#include "zufall.h"
#include <gpa/input>
#include <vector>
#include <map>
#include <time.h>
using namespace std;

int height = 21;
int width = 12;
int row = 12;
int score = 0;
double time_till_fall = 0.5;
map <int, int> board;

void draw_board(vector<int> active_block)
{

	platziere_cursor(0, 0);

	unsigned char vertical_pipe = 186;
	unsigned char horizontal_pipe = 205;
	unsigned char corner_l = 200;
	unsigned char corner_r = 188;
	unsigned char block = 219;
	unsigned char leer = 246;

	int blocks = 0;

	cout << "Score:" << score << "\n";

	for (int i = 0; i < height; ++i)
	{

		for (int i2 = 0; i2 < width; ++i2)
		{
			if (board[blocks] == 1 || board[blocks] == 2)
			{
				cout << block;
			}
			else if (board[blocks] == 3 && blocks > 11)
			{
				cout << vertical_pipe;
			}
			else if (blocks > 12)
			{
				cout << leer;
			}

			++blocks;
		}
		cout << "\n";
	}
	cout << corner_l;
	for (int g = 0; g < 10; ++g)
	{
		cout << horizontal_pipe;
	}
	cout << corner_r;
}


void create_map(int height, int width)
{
	for (int i = 0; i < height*width; i +=12)
	{
		if (i < 12)
		{
			board[i] = 3;
			board[i + 1] = 3;
			board[i + 2] = 3;
			board[i + 3] = 3;
			board[i + 4] = 3;
			board[i + 5] = 3;
			board[i + 6] = 3;
			board[i + 7] = 3;
			board[i + 8] = 3;
			board[i + 9] = 3;
			board[i + 10] = 3;
			board[i + 11] = 3;
		}
		else
		{
			board[i] = 3;
			board[i + 1] = 0;
			board[i + 2] = 0;
			board[i + 3] = 0;
			board[i + 4] = 0;
			board[i + 5] = 0;
			board[i + 6] = 0;
			board[i + 7] = 0;
			board[i + 8] = 0;
			board[i + 9] = 0;
			board[i + 10] = 0;
			board[i + 11] = 3;
		}
	}
}

void init()
{
	vector<int> active_block = { 0, 0, 0, 0, 0};
	create_map(height, width);
}

bool game_over(int doubled)
{
	if (board[13] ==2  || board[14]==2 || board[15]==2 || board[16]==2 || board[17]==2 || board[18]==2 || board[19]==2 || board[20]==2 || board[21]== 2 || board[22]==2 || board[23]==2 || board[24]==2)
	{
		platziere_cursor(0, 0);
		cout << "Game Over!\n" << "Your Score : " << score;
		return true;
	}
	else { return false; }
}


vector<int> random_block()
{
	int random_start = zufallszahl_kleiner_als(9)+12;
	int random_block = 0; // zufallszahl_kleiner_als(6);
	int random_direction = zufallszahl_kleiner_als(4);

	vector<int> active_block;


	switch (random_block)
	{
	case 0: // square
		active_block = { random_start + 1, random_start + 2, random_start + 13, random_start + 14 ,0 };
		break;
	case 1: // triangle
		active_block = { random_start + 1, random_start + 2, random_start + 3, random_start + 14, 1 };
		break;
	case 2: // long
		active_block = { random_start + 1, random_start + 13, random_start + 25, random_start + 37, 2 };
		break;
	case 3: // L
		active_block = { random_start + 1, random_start + 13, random_start + 25, random_start + 26, 3 };
		break;
	case 4: // reverse L
		active_block = { random_start + 2, random_start + 14, random_start + 26, random_start + 25, 4 };
		break;
	case 5: // z
		active_block = { random_start + 1, random_start + 2, random_start + 14, random_start + 15, 5 };
		break;
	case 6: // reverse z
		active_block = { random_start + 2, random_start + 3, random_start + 13, random_start + 14, 6 };
		break;
	}




		return active_block;


}

void write_block(vector<int> active_block)
{
	board[active_block[0]] = 1;
	board[active_block[1]] = 1;
	board[active_block[2]] = 1;
	board[active_block[3]] = 1;
}

void erase_block(vector<int> active_block)
{
	board[active_block[0]] = 0;
	board[active_block[1]] = 0;
	board[active_block[2]] = 0;
	board[active_block[3]] = 0;
}



void save_block(vector<int> active_block)
{
	board[active_block[0]] = 2;
	board[active_block[1]] = 2;
	board[active_block[2]] = 2;
	board[active_block[3]] = 2;
}

int vertical_collide(vector<int>active_block)
{
	int check = 0;

	if (board[active_block[0] + row] == 2 || board[active_block[1] + row] == 2 || board[active_block[2] + row] == 2 || board[active_block[3] + row] == 2)
	{
		check = 1;// hit another block
	}
	else if (active_block[0] + row > height*width || active_block[1] + row > height*width || active_block[2] + row > height*width || active_block[3] + row > height*width)
	{
		check = 2;// hit the ground
	}

	return check;
}

int horizontal_collide(vector<int> active_block)
{
	int check = 0;

	if (board[active_block[0] + 1] != 0 || board[active_block[1] + 1] != 0 || board[active_block[2] + 1] != 0 || board[active_block[3] + 1] != 0)
	{
		check = 1;//right
	}
	else
	if (board[active_block[0] - 1] != 0 || board[active_block[1] - 1] != 0 || board[active_block[2] - 1] != 0 || board[active_block[3] - 1] != 0)
	{
		check = 2;//left
	}
	
	return check;
}

vector<int> fall(vector<int> active_block)
{
	if (vertical_collide(active_block) == 0)
	{
		active_block = { active_block[0] + row, active_block[1] + row, active_block[2] + row, active_block[3] + row, active_block[4] };

		board[active_block[0]] = 1;
		board[active_block[1]] = 1;
		board[active_block[2]] = 1;
		board[active_block[3]] = 1;
	}

	return active_block;
}

vector<int> rotate(vector<int> active_block)
{
	// lässt sich das irgendwie automatisieren?

	return active_block;
}

vector<int> move(vector<int> active_block)
{
	if (taste_wurde_gedrueckt())
	{
		int key = gedrueckte_taste();


		if (key == 72)
		{
			active_block = rotate(active_block);
		}
		if (key == 75 && horizontal_collide(active_block) != 2)
		{
			active_block = { active_block[0] - 1, active_block[1] - 1, active_block[2] - 1, active_block[3] - 1, active_block[4] };
		}
		if (key == 77 && horizontal_collide(active_block) != 1)
		{
			active_block = { active_block[0] + 1, active_block[1] + 1, active_block[2] + 1, active_block[3] + 1, active_block[4] };
		}
		if (key == 80 && vertical_collide(active_block) == 0)
		{
			active_block = { active_block[0] + row, active_block[1] + row, active_block[2] + row, active_block[3] + row, active_block[4] };
		}
		if (key == 13){

			while (!vertical_collide(active_block))
			{
				active_block = { active_block[0] + row, active_block[1] + row, active_block[2] + row, active_block[3] + row, active_block[4] };
			}
		}

	}
		return active_block;
	
}


void checkfullrow()
{

	for (int r = height*width; r > 12; r -= row)
	{
	
		while (
			board[r + 1] == 2 &&
			board[r + 2] == 2 &&
			board[r + 3] == 2 &&
			board[r + 4] == 2 &&
			board[r + 5] == 2 &&
			board[r + 6] == 2 &&
			board[r + 7] == 2 &&
			board[r + 8] == 2 &&
			board[r + 9] == 2 &&
			board[r + 10] == 2
			)
		{
			for (int rx = r; rx > 12; rx -=12)
			{
				board[rx + 1] = board[rx - 11];
				board[rx + 2] = board[rx - 10];
				board[rx + 3] = board[rx - 9];
				board[rx + 4] = board[rx - 8];
				board[rx + 5] = board[rx - 7];
				board[rx + 6] = board[rx - 6];
				board[rx + 7] = board[rx - 5];
				board[rx + 8] = board[rx - 4];
				board[rx + 9] = board[rx - 3];
				board[rx + 10] = board[rx - 2];
			}
			++score;
		}

	}


}


void wait(double seconds)
{
clock_t wait;
wait = clock() + seconds*CLOCKS_PER_SEC;
while (clock() < wait){};
}


void main()
{
	init();

	vector<int> active_block;

	while (!game_over(0))
	{
		active_block = random_block();
		write_block(active_block);
		draw_board(active_block);
		while (vertical_collide(active_block) == 0)
		{
			erase_block(active_block);
			
			clock_t wait;
			wait = clock() + time_till_fall*CLOCKS_PER_SEC;
			while (clock() < wait)
			{
				erase_block(active_block);
				active_block = move(active_block);
				write_block(active_block);
				draw_board(active_block);
			}
			erase_block(active_block);
			active_block = fall(active_block);
			write_block(active_block);
			draw_board(active_block);
		}
		save_block(active_block);
		checkfullrow();
		draw_board(active_block);
	}
}