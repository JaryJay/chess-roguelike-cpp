#pragma once
#include "BoardState.h"
#include "Renderer.h"

class Game
{
public:
    void start();
    void process();
    void draw();
    void end();

    Game(const Renderer& renderer, const Window& window);

    Renderer renderer;
    Window window;

    std::shared_ptr<Texture2D> texture;
    std::unordered_map<std::string, std::shared_ptr<Texture2DRegion>> textureRegions;
    BoardState boardState;
    int selectedPieceId = 0;
    glm::ivec2 selectedPiecePos{};
};
