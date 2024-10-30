#include "Team.h"
#include <stdexcept>

bool are_hostile(const Team t1, const Team t2)
{
	return t1 != t2;
}

bool are_friendly(const Team t1, const Team t2)
{
	return t1 == t2;
}

std::string to_string(const Team t)
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

