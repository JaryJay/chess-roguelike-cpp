#pragma once

#include "src/math/Vector2i.h"
#include "PieceType.h"
#include "BoardState.h"
#include "Team.h"
#include <vector>

class Piece
{
public:
	Piece(Vector2i pos, PieceType type, Team team) : _pos(pos), _type(type), _team(team)
	{
		_id = generate_id();
	}

	std::vector<Move> get_available_moves(BoardState& b_state) const;
	float get_worth() const;
	Piece duplicate() const;
	bool equals(Piece& other) const;

	int id() const;
	Vector2i pos() const;
	PieceType type() const;
	Team team() const;

private:
	int _id;
	Vector2i _pos;
	PieceType _type;
	Team _team;

	Piece(int id, Vector2i pos, PieceType type, Team team) : _id(id), _pos(pos), _type(type), _team(team) {}

	static int _next_id;
	static int generate_id();

	std::vector<Move> king_get_available_squares(BoardState& b) const;
	std::vector<Move> queen_get_available_squares(BoardState& b) const;
	std::vector<Move> rook_get_available_squares(BoardState& b) const;
	std::vector<Move> bishop_get_available_squares(BoardState& b) const;
	std::vector<Move> knight_get_available_squares(BoardState& b) const;
	std::vector<Move> pawn_get_available_squares(BoardState& b) const;
};

