#include "BoardState.h"
#include <FastNoiseLite.h>
#include <random>

#include <ranges>
#include <glm/vec2.hpp>

constexpr unsigned int MAX_X = 12;
constexpr unsigned int MAX_Y = 12;
constexpr float THRESHOLD = 0.35f;

BoardState generateBoardStateWithoutPieces()
{
    // Generate a seed
    std::vector<glm::ivec2> tentativeTilePositions{};

    FastNoiseLite noise;
    noise.SetSeed(std::rand()); // NOLINT(cert-msc30-c, cert-msc50-cpp)
    noise.SetFrequency(7.0f);
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

    for (int y = 0; y < MAX_Y; ++y)
    {
        for (int x = 0; x < MAX_X; ++x)
        {
            const float val = (noise.GetNoise(x + 0.5f, y + 0.5f) + 1.0f) * 0.5f;
            const float distToCenter = glm::distance(glm::vec2(x, y), glm::vec2(MAX_X / 2, MAX_Y / 2));
            const float normalizedDist = distToCenter / glm::distance(glm::vec2(0, 0), glm::vec2(MAX_X / 2, MAX_Y / 2));

            const float modifiedVal = val * (1 - normalizedDist);
            if (modifiedVal > THRESHOLD)
                tentativeTilePositions.emplace_back(x, y);
        }
    }

    // Prune tiles that have 0 adjacent tiles
    std::set<glm::ivec2> tilePositions{};
    for (const auto& pos : tentativeTilePositions)
    {
        int adjacentTiles = 0;
        for (int y = -1; y <= 1; ++y)
        {
            for (int x = -1; x <= 1; ++x)
            {
                if (x == 0 && y == 0)
                    continue;

                glm::ivec2 newPos = pos + glm::ivec2(x, y);
                if (std::ranges::find(tentativeTilePositions, newPos) != tentativeTilePositions.end())
                    ++adjacentTiles;
            }
        }

        if (adjacentTiles > 0)
            tilePositions.insert(pos);
    }

    return {tilePositions, {}, Team::PLAYER};
}

bool BoardState::isEndState() const
{
    return false;
}

std::unique_ptr<BoardState> BoardState::simulateMove(const Move& move) const
{
    assert(hasTile(move.from));
    assert(hasPiece(move.to));
    assert(are_friendly(getPieceCopy(move.to).team(), currentTurn));
    assert(hasTile(move.to));
    assert(!hasPiece(move.to) || are_hostile( getPieceCopy(move.to).team(), getPieceCopy(move.from).team() ));

    auto newBoardState = duplicate();

    return newBoardState;
}

std::vector<Move> BoardState::getLegalMoves() const
{
    return std::vector<Move>();
}

bool BoardState::isKingAlive(Team team) const
{
    return false;
}

bool BoardState::isKingInCheck(Team team) const
{
    return false;
}

std::unique_ptr<BoardState> BoardState::duplicate() const
{
    const std::set<glm::ivec2> newTiles = {tiles};
    const std::unordered_map<glm::ivec2, Piece> newPieces = {pieces};


    return std::make_unique<BoardState>(newTiles, newPieces, currentTurn);
}

bool BoardState::hasTile(const glm::ivec2& pos) const
{
    return tiles.contains(pos);
}

bool BoardState::hasPiece(const glm::ivec2& pos) const
{
    return pieces.contains(pos);
}

Piece BoardState::getPieceCopy(const glm::ivec2& pos) const
{
    return pieces.at(pos);
}

BoardState::BoardState(const std::set<glm::ivec2>& tiles, const std::unordered_map<glm::ivec2, Piece>& pieces,
                       const Team team) : tiles(tiles), pieces(pieces), currentTurn(team)
{
}

BoardState::~BoardState() = default;
