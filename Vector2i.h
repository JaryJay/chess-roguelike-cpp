#pragma once

#include <string>

struct Vector2i
{
	int x, y;

    Vector2i(int x = 0, int y = 0) : x(x), y(y) {}

    Vector2i operator+(const Vector2i& o) const {
        return Vector2i(x + o.x, y + o.y);
    }

    bool operator==(const Vector2i& o) const {
        return x == o.x && y == o.y;
    }

    // Function to display the point
    std::string to_string() const {
        return "Vector2i(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

const Vector2i ZERO(0, 0);
const Vector2i UP(0, -1);
const Vector2i DOWN(0, 1);
const Vector2i RIGHT(1, 0);
const Vector2i LEFT(-1, 0);

