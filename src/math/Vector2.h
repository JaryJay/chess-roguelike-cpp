#pragma once

#include <string>

struct Vector2
{
    float x, y;

    Vector2(int x = 0, int y = 0) : x(x), y(y) {}

    Vector2 operator+(const Vector2& o) const {
        return Vector2(x + o.x, y + o.y);
    }

    bool operator==(const Vector2& o) const {
        return x == o.x && y == o.y;
    }

    // Function to display the point
    std::string to_string() const {
        return "Vector2(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

const Vector2 ZERO(0, 0);
const Vector2 UP(0, -1);
const Vector2 DOWN(0, 1);
const Vector2 RIGHT(1, 0);
const Vector2 LEFT(-1, 0);

