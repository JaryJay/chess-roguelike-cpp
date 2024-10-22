#include "Piece.h"
#include "PieceType.h"
#include <stdexcept>
#include <cassert>

std::vector<Move> Piece::get_available_moves(BoardState& b) const
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
	}
}

Piece Piece::duplicate() const
{
	return Piece(id(), pos(), type(), team());
}

bool Piece::equals(Piece& o) const
{
	return id() == o.id() && pos() == o.pos() && type() == o.type() && team() == o.team();
}

int Piece::id() const
{
	return _id;
}

Vector2i Piece::pos() const
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

const std::vector<Vector2i> FOUR_DIRECTIONS = {
	Vector2i(1, 0),
	Vector2i(0, 1),
	Vector2i(-1, 0),
	Vector2i(0, -1),
};
const std::vector<Vector2i> DIAGONAL_DIRECTIONS = {
	Vector2i(1, 1),
	Vector2i(-1, 1),
	Vector2i(-1, -1),
	Vector2i(1, -1),
};
const std::vector<Vector2i> EIGHT_DIRECTIONS = {
	Vector2i(1, 0),
	Vector2i(1, 1),
	Vector2i(0, 1),
	Vector2i(-1, 1),
	Vector2i(-1, 0),
	Vector2i(-1, -1),
	Vector2i(0, -1),
	Vector2i(1, -1),
};
std::vector<Move> Piece::king_get_available_squares(BoardState& b) const
{
	assert(type() == KING, "Must be correct type");
	std::vector<Move> moves;

	for (Vector2i dir : EIGHT_DIRECTIONS)
	{
		auto dest = pos() + dir;
		if (!b.has_tile(dest)) continue;

		if (b.has_piece(dest))
		{
			if (are_friendly(b.get_piece(dest)->team(), team())) continue;
			moves.push_back(Move(id(), pos(), dest, CAPTURE));
		}
		moves.push_back(Move(id(), pos(), dest));
	}

	// TODO: Filter out moves that would put king in check

	return moves;
}

std::vector<Move> Piece::queen_get_available_squares(BoardState& b) const
{
	assert(type() == QUEEN, "Must be correct type");
	std::vector<Move> moves;

	for (Vector2i dir : EIGHT_DIRECTIONS)
	{
		auto dest = pos() + dir;
		for (int i = 0; i < 16; ++i)
		{
			if (!b.has_tile(dest)) break;

			if (b.has_piece(dest))
			{
				if (are_friendly(b.get_piece(dest)->team(), team())) break;
				moves.push_back(Move(id(), pos(), dest, CAPTURE));
			}
			moves.push_back(Move(id(), pos(), dest));

			dest = dest + dir;
		}
	}

	return moves;
}

std::vector<Move> Piece::rook_get_available_squares(BoardState& b) const
{
	assert(type() == ROOK, "Must be correct type");
	std::vector<Move> moves;

	for (Vector2i dir : FOUR_DIRECTIONS)
	{
		auto dest = pos() + dir;
		for (int i = 0; i < 16; ++i)
		{
			if (!b.has_tile(dest)) break;

			if (b.has_piece(dest))
			{
				if (are_friendly(b.get_piece(dest)->team(), team())) break;
				moves.push_back(Move(id(), pos(), dest, CAPTURE));
			}
			moves.push_back(Move(id(), pos(), dest));

			dest = dest + dir;
		}
	}

	return moves;
}

std::vector<Move> Piece::bishop_get_available_squares(BoardState& b) const
{
	assert(type() == BISHOP, "Must be correct type");
	std::vector<Move> moves;

	for (Vector2i dir : DIAGONAL_DIRECTIONS)
	{
		auto dest = pos() + dir;
		for (int i = 0; i < 16; ++i)
		{
			if (!b.has_tile(dest)) break;

			if (b.has_piece(dest))
			{
				if (are_friendly(b.get_piece(dest)->team(), team())) break;
				moves.push_back(Move(id(), pos(), dest, CAPTURE));
			}
			moves.push_back(Move(id(), pos(), dest));

			dest = dest + dir;
		}
	}

	return moves;
}

const std::vector<Vector2i> KNIGHT_DIRECTIONS = {
	Vector2i(2, 1),
	Vector2i(1, 2),
	Vector2i(-1, 2),
	Vector2i(-2, 1),
	Vector2i(-2, -1),
	Vector2i(-1, -2),
	Vector2i(1, -2),
	Vector2i(2, -1),
};
std::vector<Move> Piece::knight_get_available_squares(BoardState& b) const
{
	assert(type() == KNIGHT, "Must be correct type");
	std::vector<Move> moves;

	for (Vector2i dir : KNIGHT_DIRECTIONS)
	{
		auto dest = pos() + dir;
		if (!b.has_tile(dest)) continue;

		if (b.has_piece(dest))
		{
			if (are_friendly(b.get_piece(dest)->team(), team())) continue;
			moves.push_back(Move(id(), pos(), dest, CAPTURE));
		}
		moves.push_back(Move(id(), pos(), dest));
	}

	return moves;
}

std::vector<Move> Piece::pawn_get_available_squares(BoardState& b) const
{
	assert(type() == PAWN, "Must be correct type");

	Vector2i forward = team() == PLAYER ? Vector2i(0, -1) : Vector2i(0, 1);
	
	auto capture_directions = { forward + Vector2i(-1, 0), forward + Vector2i(1, 0)	};

	std::vector<Move> moves;
	// Tile in front
	if (b.has_tile(pos() + forward) && !b.has_piece(pos() + forward))
	{
		auto dest = pos() + forward;

		if (b.has_tile(dest + forward))
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
	for (Vector2i capture_dir : capture_directions) {
		auto dest = pos() + capture_dir;
		if (!b.has_tile(dest) || !b.has_piece(dest) || !are_hostile(team(), b.get_piece(dest)->team()))
			continue;

		if (b.has_tile(dest + forward))
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
