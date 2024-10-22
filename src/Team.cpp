#include "Team.h"
#include <stdexcept>

bool are_hostile(Team t1, Team t2)
{
	return t1 != t2;
}

bool are_friendly(Team t1, Team t2)
{
	return t1 == t2;
}

std::string to_string(Team t)
{
	switch (t)
	{
	case PLAYER:
		return "Player";
	case ENEMY:
		return "Enemy";
	default:
		throw std::logic_error("Unexpected team: " + t);
	}
}

