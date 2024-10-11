#include "BoardState.h"

bool BoardState::is_end_state()
{
	return false;
}

BoardState BoardState::simulate_move(const Move& move)
{
	return BoardState();
}

std::vector<Move> BoardState::get_legal_moves()
{
	return std::vector<Move>();
}

bool BoardState::is_king_alive(const Team& team)
{
	return false;
}

bool BoardState::is_king_in_check(const Team& team)
{
	return false;
}

BoardState BoardState::duplicate()
{
	return BoardState();
}

bool BoardState::has_tile(const Vector2i& pos)
{
	return false;
}

bool BoardState::has_piece(const Vector2i& pos)
{
	return false;
}

PieceState& BoardState::get_piece(const Vector2i& pos)
{
	return NULL;
}

BoardState::BoardState() : tiles(), current_turn(&Team::PLAYER)
{
}

BoardState::~BoardState()
{
}
