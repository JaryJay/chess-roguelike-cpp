#pragma once
#include <glm/vec2.hpp>

typedef unsigned __int8 MoveFlags;

enum {
	//RESERVED_A = 128,
	PROMOTE_TO_QUEEN = 64,
	PROMOTE_TO_ROOK = 32,
	PROMOTE_TO_BISHOP = 16,
	PROMOTE_TO_KNIGHT = 8,
	//RESERVED_B = 4,
	CAPTURE = 2,
	//RESERVED_C = 1,
};

struct Move {
	int piece_id;
	glm::ivec2 from;
	glm::ivec2 to;
	MoveFlags flags;

	Move(const int piece_id, const glm::ivec2 from, const glm::ivec2 to, const MoveFlags flags = 0) :
		piece_id(piece_id), from(from), to(to), flags(flags) {}
};