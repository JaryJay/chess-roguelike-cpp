#include "Game.h"

#include <iostream>
#include <ostream>

void Game::start()
{
    texture = std::make_shared<Texture2D>("assets/pieces_sprite_sheet.png");

    textureRegions["whiteTile"] = std::make_shared<Texture2DRegion>(*texture, glm::vec2(72, 0), glm::vec2(88, 16));
    textureRegions["darkTile"] = std::make_shared<Texture2DRegion>(*texture, glm::vec2(88, 0), glm::vec2(104, 16));
    textureRegions["whitePawn"] = std::make_shared<Texture2DRegion>(*texture, glm::vec2(48, 40), glm::vec2(61, 56));
}

void Game::process()
{
}

void Game::draw()
{
    // Rendering commands here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    const auto whiteTile = textureRegions["whiteTile"];
    const auto darkTile = textureRegions["darkTile"];
    const auto whitePawn = textureRegions["whitePawn"];

    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            if ((x + y) % 2 == 0)
            {
                renderer.drawTextureRegion(*whiteTile, glm::vec2(100, 100) + glm::vec2(x, y) * 16.0f * 4.0f, 4.0f);
            } else
            {
                renderer.drawTextureRegion(*darkTile, glm::vec2(100, 100) + glm::vec2(x, y) * 16.0f * 4.0f, 4.0f);
            }
        }
    }


    renderer.drawTextureRegion(*whitePawn, glm::vec2(200.0f, 200.0f), 4.0f);
}

void Game::end()
{
}
