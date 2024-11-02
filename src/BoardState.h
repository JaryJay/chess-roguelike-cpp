#pragma once
#include "Move.h"
#include <unordered_map>
#include <memory>
#include <glm/vec2.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"
#include "Team.h"
#include "Piece.h"

class BoardState
{
public:
	[[nodiscard]] bool isEndState() const;
	[[nodiscard]] std::unique_ptr<BoardState> simulateMove(const Move& move) const;
	[[nodiscard]] std::vector<Move> getLegalMoves() const;
	[[nodiscard]] bool isKingAlive(Team team) const;
	[[nodiscard]] bool isKingInCheck(Team team) const;
	[[nodiscard]] std::unique_ptr<BoardState> duplicate() const;
	[[nodiscard]] bool hasTile(const glm::ivec2& pos) const;
	[[nodiscard]] bool hasPiece(const glm::ivec2& pos) const;
	[[nodiscard]] std::unique_ptr<Piece> getPiece(const glm::ivec2& pos) const;
	[[nodiscard]] std::vector<Piece> getPieces() const;

	BoardState();
	~BoardState();
private:
	std::unordered_map<glm::ivec2, bool> tiles;
	std::unordered_map<glm::ivec2, Piece> pieces;
	Team current_turn;

	explicit BoardState(Team team);
};

