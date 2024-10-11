#pragma once
#include "Move.h"
#include <unordered_map>
#include "PieceState.h"
class BoardState
{
public:
	bool is_end_state();
	BoardState simulate_move(const Move& move);
	std::vector<Move> get_legal_moves();
	bool is_king_alive(const Team& team);
	bool is_king_in_check(const Team& team);
	BoardState duplicate();
	bool has_tile(const Vector2i& pos);
	bool has_piece(const Vector2i& pos);
	PieceState get_piece(const Vector2i& pos);

	BoardState();
	~BoardState();
private:
	std::unordered_map<Vector2i, bool> tiles;
	std::unordered_map<Vector2i, PieceState&> pieces;
	Team& current_turn;
};

