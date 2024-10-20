#include "BoardState.h"

bool BoardState::is_end_state() const
{
	return false;
}

std::unique_ptr<BoardState> BoardState::simulate_move(const Move& move) const
{
	return std::make_unique<BoardState>();
}

std::vector<Move> BoardState::get_legal_moves() const
{
	return std::vector<Move>();
}

bool BoardState::is_king_alive(Team team) const
{
	return false;
}

bool BoardState::is_king_in_check(Team team) const
{
	return false;
}

std::unique_ptr<BoardState> BoardState::duplicate() const
{
	return std::make_unique<BoardState>();
}

bool BoardState::has_tile(const Vector2i& pos) const
{
	return false;
}

bool BoardState::has_piece(const Vector2i& pos) const
{
	return false;
}

std::unique_ptr<Piece> BoardState::get_piece(const Vector2i& pos) const
{
	return NULL;
}

BoardState::BoardState() : tiles(), current_turn(PLAYER)
{
}

BoardState::BoardState(Team team) : tiles(), current_turn(team)
{
}

BoardState::~BoardState()
{
}
