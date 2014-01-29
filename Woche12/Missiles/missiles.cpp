#include "graphics.h"
#include "random.h"
#include "rocket.h"
#include <algorithm>
#include <iostream>
#include <vector>

int ENEMY_DELAY = 2000;
const double ENEMY_VELOCITY = 25;
const word ENEMY_COLOR = 0xff7f7f;

const int MAX_DEFENSE_ROCKETS = 3;
const double DEFENSE_VELOCITY = 100;
const word DEFENSE_COLOR = 0x7fff7f;

const int EXPLOSION_RADIUS = 40;

std::vector<rocket> defense_rockets; //copy r
std::vector<rocket> enemy_rockets; //copy e

bool game_over = false;
int attack_time = 0;
int bx = 400;
int by = 600;
int tx = 0;
int ty = 0;
int originY = 0;
int current_rockets = 0;
int destroyed = 0;
int started = 0;
int played = 0;
int shots = 0;
int highscore = 0;

void initialize()
{
	attack_time = current_time;
	started = current_time;
}

void reset(){
	game_over = false;
	attack_time = 0;
	bx = 400;
	by = 600;
	tx = 0;
	ty = 0;
	originY = 0;
	current_rockets = 0;
	destroyed = 0;
	started = 0;
	shots = 0;
	played = 0;
	ENEMY_DELAY = 2000;
	defense_rockets.erase(defense_rockets.begin(), defense_rockets.end());
	enemy_rockets.erase(enemy_rockets.begin(), enemy_rockets.end());
	initialize();

}

void draw_crosshair(const rocket& r)
{
	draw_pixel(r.target.x - 1, r.target.y, DEFENSE_COLOR);
	draw_pixel(r.target.x + 1, r.target.y, DEFENSE_COLOR);
	draw_pixel(r.target.x, r.target.y - 1, DEFENSE_COLOR);
	draw_pixel(r.target.x, r.target.y + 1, DEFENSE_COLOR);
}

void render()
{
	for (const rocket& r : defense_rockets)
	{
		draw_rocket(r);
		draw_crosshair(r);
	}
	for (const rocket& r : enemy_rockets)
	{
		draw_rocket(r);
	}
}

void check_game_over()
{
	auto first_arrived = std::find_if_not(enemy_rockets.begin(), enemy_rockets.end(), rocket_is_underway);
	if (first_arrived != enemy_rockets.end())
	{
		game_over = true;
	}
}

void spawn_new_enemy_rocket()
{
	double originX = random_double_between(10, 790);
	double tx = random_double_between(10, 790);
	enemy_rockets.push_back(make_rocket(originX, originY, tx, 606, ENEMY_VELOCITY, ENEMY_COLOR));
}

void key_pressed(int keycode)
{
	if (keycode == 37 && bx > 5) bx -= 5;
	else if (keycode == 39 && bx < 795) bx += 5;
}

void mouse_pressed(int x, int y, int button)
{
	if (current_rockets < MAX_DEFENSE_ROCKETS){
		defense_rockets.push_back(make_rocket(bx, by, x, y, DEFENSE_VELOCITY, DEFENSE_COLOR));
		current_rockets++;
		shots++;
	}
}


bool enemy_was_stopped(const rocket& r)
{

	return !(r.flight_duration > 0);
}

void destroy_enemy_rockets(const rocket& r)
{
	for (rocket& e : enemy_rockets)
	{
		double distance = length(e.position - r.position);
		if (distance < EXPLOSION_RADIUS)
		{
			e.flight_duration = 0;
		}
	}
}


void explode_defense_rocket()
{
	auto first_expired_rocket = std::partition(defense_rockets.begin(), defense_rockets.end(), rocket_is_underway);

	for (auto it = first_expired_rocket; it != defense_rockets.end(); it++){
		current_rockets--;
	}

	if (first_expired_rocket != defense_rockets.end())
	{
		std::for_each(first_expired_rocket, defense_rockets.end(), destroy_enemy_rockets);
	}


	auto first_stopped = std::remove_if(enemy_rockets.begin(), enemy_rockets.end(), enemy_was_stopped);
	int abstand = enemy_rockets.end() - first_stopped;
	destroyed += abstand;
	ENEMY_DELAY -= 30 * abstand;
	enemy_rockets.erase(first_stopped, enemy_rockets.end());
	defense_rockets.erase(first_expired_rocket, defense_rockets.end());

}

void update()
{

	if (!game_over)
	{
		if (current_time - attack_time >= ENEMY_DELAY)
		{
			spawn_new_enemy_rocket();
			attack_time += ENEMY_DELAY;
		}
		for (rocket& r : defense_rockets)
		{
			update_rocket_position(r);
		}
		explode_defense_rocket();
		auto first_arrived = std::find_if_not(enemy_rockets.begin(), enemy_rockets.end(), rocket_is_underway);
		if (first_arrived != enemy_rockets.end())
		{
			game_over = true;
		}
		for (rocket& r : enemy_rockets)
		{
			update_rocket_position(r);
		}

	}
	else{
		played = (current_time - started) / 1000;
		int score = destroyed * 100 - shots * 20 + played * 20;
		std::cout << "You countered " << destroyed << " rockets, utilizing " << shots << " rockets and you withstand for " << played << " seconds \n";
		if (score > highscore){
			highscore = score;
			std::cout << "Current Highscore " << highscore << "! You scored " << score << " Points, YAY NEW HIGHSCORE :)\n";
		}
		else{
			std::cout << "Current Highscore " << highscore << "! You scored " << score << " Points, aww try again :(\n";
		}
		reset();
	}
}
