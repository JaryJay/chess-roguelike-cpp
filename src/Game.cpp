#include "Game.h"

#include <iostream>
#include <ostream>

#include "ArmyGenerator.h"

using namespace glm;

Game::Game(const Renderer& renderer, const Window& window)
    : renderer(renderer),
      window(window),
      boardState(generateBoardStateWithoutPieces())
{
}

void Game::start()
{
    generateArmy(1300, boardState, ENEMY);

    texture = std::make_shared<Texture2D>("assets/pieces_sprite_sheet.png");

    textureRegions["whiteTile"] = std::make_shared<Texture2DRegion>(*texture, vec2(72, 0), vec2(88, 16));
    textureRegions["darkTile"] = std::make_shared<Texture2DRegion>(*texture, vec2(88, 0), vec2(104, 16));
    textureRegions["whitePawn"] = std::make_shared<Texture2DRegion>(*texture, vec2(48, 40), vec2(61, 56));
}

void Game::process()
{
}

void Game::draw()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    const auto whiteTile = textureRegions["whiteTile"];
    const auto darkTile = textureRegions["darkTile"];
    const auto whitePawn = textureRegions["whitePawn"];

    for (const auto tile : boardState.tiles)
    {
        const auto textureRegion = (tile.x + tile.y) % 2 == 0 ? whiteTile : darkTile;
        renderer.drawTextureRegion(*textureRegion, vec2(tile.x * 16.0f, tile.y * 16.0f), 4.0f);
    }


    renderer.drawTextureRegion(*whitePawn, vec2(200.0f, 200.0f), 4.0f);
}

void Game::end()
{
    textureRegions.clear();
}
