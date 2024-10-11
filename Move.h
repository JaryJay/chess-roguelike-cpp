#pragma once
#include "Vector2i.h"
struct Move {
	int piece_id;
	Vector2i from;
	Vector2i to;

	Move(int piece_id, Vector2i from, Vector2i to) : piece_id(piece_id), from(from), to(to) {}
};