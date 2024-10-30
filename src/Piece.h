#pragma once

#include <vector>
#include <glm/vec2.hpp>

class BoardState;
#include "Move.h"
#include "PieceType.h"
#include "Team.h"

class Piece
{
public:
	Piece(const glm::ivec2 pos, const PieceType type, const Team team) : _pos(pos), _type(type), _team(team)
	{
		_id = generate_id();
	}

	[[nodiscard]] std::vector<Move> get_available_moves(const BoardState& b) const;
	[[nodiscard]] float get_worth() const;
	[[nodiscard]] Piece duplicate() const;
	[[nodiscard]] bool equals(const Piece& other) const;

	[[nodiscard]] int id() const;
	[[nodiscard]] glm::ivec2 pos() const;
	[[nodiscard]] PieceType type() const;
	[[nodiscard]] Team team() const;

private:
	int _id;
	glm::ivec2 _pos;
	PieceType _type;
	Team _team;

	Piece(const int id, const glm::ivec2 pos, const PieceType type, const Team team) : _id(id), _pos(pos), _type(type), _team(team) {}

	static int _next_id;
	static int generate_id();

	[[nodiscard]] std::vector<Move> king_get_available_squares(const BoardState& b) const;
	[[nodiscard]] std::vector<Move> queen_get_available_squares(const BoardState& b) const;
	[[nodiscard]] std::vector<Move> rook_get_available_squares(const BoardState& b) const;
	[[nodiscard]] std::vector<Move> bishop_get_available_squares(const BoardState& b) const;
	[[nodiscard]] std::vector<Move> knight_get_available_squares(const BoardState& b) const;
	[[nodiscard]] std::vector<Move> pawn_get_available_squares(const BoardState& b) const;
};

