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
	[[nodiscard]] bool is_end_state() const;
	[[nodiscard]] std::unique_ptr<BoardState> simulate_move(const Move& move) const;
	[[nodiscard]] std::vector<Move> get_legal_moves() const;
	[[nodiscard]] bool is_king_alive(Team team) const;
	[[nodiscard]] bool is_king_in_check(Team team) const;
	[[nodiscard]] std::unique_ptr<BoardState> duplicate() const;
	[[nodiscard]] bool has_tile(const glm::ivec2& pos) const;
	[[nodiscard]] bool has_piece(const glm::ivec2& pos) const;
	[[nodiscard]] std::unique_ptr<Piece> get_piece(const glm::ivec2& pos) const;

	BoardState();
	~BoardState();
private:
	std::unordered_map<glm::ivec2, bool> tiles;
	std::unordered_map<glm::ivec2, Piece> pieces;
	Team current_turn;

	explicit BoardState(Team team);
};

