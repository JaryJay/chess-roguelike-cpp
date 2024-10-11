#pragma once

#include "Vector2i.h"
#include "PieceType.h"
#include "BoardState.h"
#include "Team.h"
#include <vector>

class PieceState
{
public:
	int id();
	Vector2i pos();
	PieceType type();
	Team team();

	PieceState(Vector2i pos, PieceType type, Team team) : _pos(pos), _type(type), _team(team)
	{
		_id = generate_id();
	}

	std::vector<Vector2i> get_available_squares(BoardState b_state);
	float get_worth();
	PieceState duplicate();
	bool equals(PieceState& other);

private:
	int _id;
	Vector2i _pos;
	PieceType _type;
	Team _team;

	PieceState(int id, Vector2i pos, PieceType type, Team team) : _id(id), _pos(pos), _type(type), _team(team) {}

	static int _next_id;
	static int generate_id();
};

