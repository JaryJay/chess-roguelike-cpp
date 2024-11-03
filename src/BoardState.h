#pragma once

#include "Move.h"
#include <unordered_map>
#include <memory>
#define GLM_FORCE_MESSAGES
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/vec2.hpp>
#include <set>

#include "glm/gtx/hash.hpp"
#include "Team.h"
#include "Piece.h"


BoardState generateBoardStateWithoutPieces();

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
	[[nodiscard]] Piece getPieceCopy(const glm::ivec2& pos) const;

	BoardState(const std::set<glm::ivec2>& tiles, const std::unordered_map<glm::ivec2, Piece>& pieces, Team team);
	~BoardState();

	std::set<glm::ivec2> tiles;
	std::unordered_map<glm::ivec2, Piece> pieces;
	Team currentTurn;
};

