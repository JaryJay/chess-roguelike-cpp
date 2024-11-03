
#include "ArmyGenerator.h"

#include <algorithm>

const std::unordered_map<PieceType, int> PIECE_COSTS = {
    {PAWN, 100},
    {KNIGHT, 300},
    {BISHOP, 300},
    {ROOK, 500},
    {QUEEN, 900},
};

PieceType generatePieceType(const int credits)
{
    if (credits < PIECE_COSTS.at(PAWN))
        return UNSET;

    std::vector<PieceType> affordableTypes;
    for (const auto& [type, cost] : PIECE_COSTS)
    {
        if (cost <= credits)
            affordableTypes.push_back(type);
    }
    assert(!affordableTypes.empty());

    return affordableTypes.at(std::rand() % affordableTypes.size()); // NOLINT(*-msc50-cpp)
}

bool sort_tiles_by_y(const glm::vec2 a, const glm::vec2 b){
    return a.y < b.y;
}

std::vector<Piece> generateArmy(int credits, const BoardState& s, const Team team)
{
    std::vector<Piece> army;

    army.emplace_back(glm::vec2(0), KING, team);

    // Generate pieces
    while (credits > 0)
    {
        PieceType t = generatePieceType(credits);
        if (t == UNSET) break;

        credits -= PIECE_COSTS.at(t);
        army.emplace_back(glm::vec2(0), t, team);
    }


    // Arrange pieces
    const auto armySize = army.size();
    assert(s.tiles.size() >= armySize && "Board does not have enough tiles");
    std::vector<glm::ivec2> tiles;
    for (const auto pos : s.tiles)
        tiles.push_back(pos);
    // Sort tiles by y
    std::ranges::sort(tiles, sort_tiles_by_y);
    // Set piece positions
    for (size_t i = 0; i < armySize; ++i)
        army.at(i).setPos(tiles.at(i));

    return army;
}
