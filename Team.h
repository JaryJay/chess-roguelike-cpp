#pragma once

#include <string>

enum Team {
	PLAYER = 20,
	ENEMY = 40,
};

bool are_hostile(Team t1, Team t2);
bool are_friendly(Team t1, Team t2);
std::string to_string(Team t);
