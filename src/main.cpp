#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "QuadMesh.h"
#include "Renderer.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Window.h"

#include "Game.h"



void processInput(const Window& window)
{
    if (window.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        window.setShouldClose(true);
}

int main()
{
    glfwInit();
    constexpr int windowWidth = 1400;
    constexpr int windowHeight = 900;
    const Window window(windowWidth, windowHeight, "Chess Roguelike");
    window.makeCurrent();

    // initialize GLAD before we call any OpenGL function
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, windowWidth, windowHeight);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const ShaderProgram shaderProgram("shaders/textureVertexShader.glsl", "shaders/textureFragmentShader.glsl");
    const QuadMesh quadMesh{};
    const Renderer renderer(shaderProgram, quadMesh, window);

    Game game(renderer, window);
    game.start();

    // Render loop
    while (!window.shouldClose())
    {
        // Input
        processInput(window);

        game.process();
        game.draw();

        // Check and call events and swap buffers
        window.swapBuffers();
        glfwPollEvents();
    }

    game.end();
    glfwTerminate();
    return 0;
}
