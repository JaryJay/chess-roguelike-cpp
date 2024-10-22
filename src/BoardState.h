#pragma once
#include "Move.h"
#include <unordered_map>
#include <memory>
#include "Piece.h"
class BoardState
{
public:
	bool is_end_state() const;
	std::unique_ptr<BoardState> simulate_move(const Move& move) const;
	std::vector<Move> get_legal_moves() const;
	bool is_king_alive(Team team) const;
	bool is_king_in_check(Team team) const;
	std::unique_ptr<BoardState> duplicate() const;
	bool has_tile(const Vector2i& pos) const;
	bool has_piece(const Vector2i& pos) const;
	std::unique_ptr<Piece> get_piece(const Vector2i& pos) const;

	BoardState();
	~BoardState();
private:
	std::unordered_map<Vector2i, bool> tiles;
	std::unordered_map<Vector2i, Piece> pieces;
	Team current_turn;

	BoardState(Team team);
};

