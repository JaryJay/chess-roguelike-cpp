#include "PieceState.h"
#include "PieceType.h"

int PieceState::id()
{
	return _id;
}

Vector2i PieceState::pos()
{
	return _pos;
}

PieceType PieceState::type()
{
	return _type;
}

Team PieceState::team()
{
	return _team;
}

std::vector<Vector2i> PieceState::get_available_squares(BoardState b_state)
{
	return std::vector<Vector2i>();
}

float PieceState::get_worth()
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

PieceState PieceState::duplicate()
{
	return PieceState(id(), pos(), type(), team());
}

bool PieceState::equals(PieceState& o)
{
	return id() == o.id() && pos() == o.pos() && type() == o.type() && team().is_friendly_to(o.team());
}

int PieceState::_next_id = 1;
int PieceState::generate_id()
{
	return _next_id++;
}


