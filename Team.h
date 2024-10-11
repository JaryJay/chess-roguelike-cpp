#pragma once

#include <string>

class Team
{
public:
	static const Team PLAYER;
	static const Team ENEMY;

	bool is_player();
	bool is_enemy();
	bool is_hostile_to(Team o);
	bool is_friendly_to(Team o);
	std::string to_string();

private:
	int key;

	Team(int k);
};

