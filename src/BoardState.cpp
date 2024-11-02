#include "BoardState.h"

#include <ranges>
#include <glm/vec2.hpp>

bool BoardState::isEndState() const
{
	return false;
}

std::unique_ptr<BoardState> BoardState::simulateMove(const Move& move) const
{
	return std::make_unique<BoardState>();
}

std::vector<Move> BoardState::getLegalMoves() const
{
	return std::vector<Move>();
}

bool BoardState::isKingAlive(Team team) const
{
	return false;
}

bool BoardState::isKingInCheck(Team team) const
{
	return false;
}

std::unique_ptr<BoardState> BoardState::duplicate() const
{
	return std::make_unique<BoardState>();
}

bool BoardState::hasTile(const glm::ivec2& pos) const
{
	return false;
}

bool BoardState::hasPiece(const glm::ivec2& pos) const
{
	return false;
}

std::unique_ptr<Piece> BoardState::getPiece(const glm::ivec2& pos) const
{
	return nullptr;
}

std::vector<Piece> BoardState::getPieces() const
{
	// get values of pieces map
	std::vector<Piece> p = {};
	for (const auto& value : pieces | std::views::values)
	{
		p.push_back(value);
	}
	return p;
}

BoardState::BoardState() : current_turn(PLAYER)
{
}

BoardState::BoardState(const Team team) : current_turn(team)
{
}

BoardState::~BoardState() = default;
