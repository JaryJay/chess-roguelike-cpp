#include "Team.h"

const int PLAYER_KEY = 15;
const int ENEMY_KEY = 20;

const Team Team::PLAYER(PLAYER_KEY);
const Team Team::ENEMY(ENEMY_KEY);

bool Team::is_player()
{
	return key == PLAYER_KEY;
}

bool Team::is_enemy()
{
	return key == ENEMY_KEY;
}

bool Team::is_hostile_to(Team o)
{
	return key != o.key;
}

bool Team::is_friendly_to(Team o)
{
	return key == o.key;
}

std::string Team::to_string()
{
	return is_player() ? "Player" : "Enemey";
}

Team::Team(int k)
{
	key = k;
}
