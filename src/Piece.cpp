#include "Piece.h"
#include "PieceType.h"
#include "BoardState.h"
#include <stdexcept>
#include <cassert>

std::vector<Move> Piece::get_available_moves(const BoardState& b) const
{
	switch (type())
	{
	case KING:
		return king_get_available_squares(b);
	case QUEEN:
		return queen_get_available_squares(b);
	case ROOK:
		return rook_get_available_squares(b);
	case BISHOP:
		return bishop_get_available_squares(b);
	case KNIGHT:
		return knight_get_available_squares(b);
	case PAWN:
		return pawn_get_available_squares(b);
	default:
		throw std::logic_error("Unexpected type: " + type());
	}
}

float Piece::get_worth() const
{
	switch (type())
	{
	case KING:
		return 1000000;
	case QUEEN:
		return 9;
	case ROOK:
		return 5;
	case BISHOP:
		return 3.2;
	case KNIGHT:
		return 3;
	case PAWN:
		return 1;
	default:
		throw std::logic_error("Unexpected type: " + type());
	}
}

Piece Piece::duplicate() const
{
	return {id(), pos(), type(), team()};
}

bool Piece::equals(const Piece& o) const
{
	return id() == o.id() && pos() == o.pos() && type() == o.type() && team() == o.team();
}

int Piece::id() const
{
	return _id;
}

glm::ivec2 Piece::pos() const
{
	return _pos;
}

PieceType Piece::type() const
{
	return _type;
}

Team Piece::team() const
{
	return _team;
}

int Piece::_next_id = 1;
int Piece::generate_id()
{
	return _next_id++;
}

// The following functions are all implementations for getting available moves.

const std::vector<glm::ivec2> FOUR_DIRECTIONS = {
	glm::ivec2(1, 0),
	glm::ivec2(0, 1),
	glm::ivec2(-1, 0),
	glm::ivec2(0, -1),
};
const std::vector<glm::ivec2> DIAGONAL_DIRECTIONS = {
	glm::ivec2(1, 1),
	glm::ivec2(-1, 1),
	glm::ivec2(-1, -1),
	glm::ivec2(1, -1),
};
const std::vector<glm::ivec2> EIGHT_DIRECTIONS = {
	glm::ivec2(1, 0),
	glm::ivec2(1, 1),
	glm::ivec2(0, 1),
	glm::ivec2(-1, 1),
	glm::ivec2(-1, 0),
	glm::ivec2(-1, -1),
	glm::ivec2(0, -1),
	glm::ivec2(1, -1),
};
std::vector<Move> Piece::king_get_available_squares(const BoardState& b) const
{
	assert(type() == KING && "Must be correct type");
	std::vector<Move> moves;

	for (glm::ivec2 dir : EIGHT_DIRECTIONS)
	{
		auto dest = pos() + dir;
		if (!b.hasTile(dest)) continue;

		if (b.hasPiece(dest))
		{
			if (are_friendly(b.getPiece(dest)->team(), team())) continue;
			moves.push_back(Move(id(), pos(), dest, CAPTURE));
		}
		moves.push_back(Move(id(), pos(), dest));
	}

	// TODO: Filter out moves that would put king in check

	return moves;
}

std::vector<Move> Piece::queen_get_available_squares(const BoardState& b) const
{
	assert(type() == QUEEN && "Must be correct type");
	std::vector<Move> moves;

	for (glm::ivec2 dir : EIGHT_DIRECTIONS)
	{
		auto dest = pos() + dir;
		for (int i = 0; i < 16; ++i)
		{
			if (!b.hasTile(dest)) break;

			if (b.hasPiece(dest))
			{
				if (are_friendly(b.getPiece(dest)->team(), team())) break;
				moves.push_back(Move(id(), pos(), dest, CAPTURE));
			}
			moves.push_back(Move(id(), pos(), dest));

			dest = dest + dir;
		}
	}

	return moves;
}

std::vector<Move> Piece::rook_get_available_squares(const BoardState& b) const
{
	assert(type() == ROOK && "Must be correct type");
	std::vector<Move> moves;

	for (glm::ivec2 dir : FOUR_DIRECTIONS)
	{
		auto dest = pos() + dir;
		for (int i = 0; i < 16; ++i)
		{
			if (!b.hasTile(dest)) break;

			if (b.hasPiece(dest))
			{
				if (are_friendly(b.getPiece(dest)->team(), team())) break;
				moves.push_back(Move(id(), pos(), dest, CAPTURE));
			}
			moves.push_back(Move(id(), pos(), dest));

			dest = dest + dir;
		}
	}

	return moves;
}

std::vector<Move> Piece::bishop_get_available_squares(const BoardState& b) const
{
	assert(type() == BISHOP && "Must be correct type");
	std::vector<Move> moves;

	for (glm::ivec2 dir : DIAGONAL_DIRECTIONS)
	{
		auto dest = pos() + dir;
		for (int i = 0; i < 16; ++i)
		{
			if (!b.hasTile(dest)) break;

			if (b.hasPiece(dest))
			{
				if (are_friendly(b.getPiece(dest)->team(), team())) break;
				moves.push_back(Move(id(), pos(), dest, CAPTURE));
			}
			moves.push_back(Move(id(), pos(), dest));

			dest = dest + dir;
		}
	}

	return moves;
}

const std::vector<glm::ivec2> KNIGHT_DIRECTIONS = {
	glm::ivec2(2, 1),
	glm::ivec2(1, 2),
	glm::ivec2(-1, 2),
	glm::ivec2(-2, 1),
	glm::ivec2(-2, -1),
	glm::ivec2(-1, -2),
	glm::ivec2(1, -2),
	glm::ivec2(2, -1),
};
std::vector<Move> Piece::knight_get_available_squares(const BoardState& b) const
{
	assert(type() == KNIGHT && "Must be correct type");
	std::vector<Move> moves;

	for (glm::ivec2 dir : KNIGHT_DIRECTIONS)
	{
		auto dest = pos() + dir;
		if (!b.hasTile(dest)) continue;

		if (b.hasPiece(dest))
		{
			if (are_friendly(b.getPiece(dest)->team(), team())) continue;
			moves.push_back(Move(id(), pos(), dest, CAPTURE));
		}
		moves.push_back(Move(id(), pos(), dest));
	}

	return moves;
}

std::vector<Move> Piece::pawn_get_available_squares(const BoardState& b) const
{
	assert(type() == PAWN && "Must be correct type");

	glm::ivec2 forward = team() == PLAYER ? glm::ivec2(0, -1) : glm::ivec2(0, 1);
	
	auto capture_directions = { forward + glm::ivec2(-1, 0), forward + glm::ivec2(1, 0)	};

	std::vector<Move> moves;
	// Tile in front
	if (b.hasTile(pos() + forward) && !b.hasPiece(pos() + forward))
	{
		auto dest = pos() + forward;

		if (b.hasTile(dest + forward))
		{
			// If pawn has reached end
			for (MoveFlags promotion_flags : { PROMOTE_TO_QUEEN, PROMOTE_TO_ROOK, PROMOTE_TO_BISHOP, PROMOTE_TO_KNIGHT })
			{
				moves.push_back(Move(id(), pos(), dest, promotion_flags));
			}
		}
		else
		{
			moves.push_back(Move(id(), pos(), dest));
		}
	}

	// Captures to the diagonal forward directions
	for (glm::ivec2 capture_dir : capture_directions) {
		auto dest = pos() + capture_dir;
		if (!b.hasTile(dest) || !b.hasPiece(dest) || !are_hostile(team(), b.getPiece(dest)->team()))
			continue;

		if (b.hasTile(dest + forward))
		{
			// If pawn has reached end
			for (MoveFlags promotion_flags : { PROMOTE_TO_QUEEN, PROMOTE_TO_ROOK, PROMOTE_TO_BISHOP, PROMOTE_TO_KNIGHT })
			{
				moves.push_back(Move(id(), pos(), dest, promotion_flags | CAPTURE));
			}
		}
		else
		{
			moves.push_back(Move(id(), pos(), dest, CAPTURE));
		}
	}

	// Tiles to the sides

	return moves;
}
