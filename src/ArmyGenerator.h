#pragma once
#include "BoardState.h"
#include "Piece.h"

std::vector<Piece> generateArmy(int credits, const BoardState& s, Team team);