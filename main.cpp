#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "QuadMesh.h"
#include "Renderer.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Window.h"

#include <glm/gtc/matrix_transform.hpp>

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
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Create texture shader
    const ShaderProgram shaderProgram("shaders/textureVertexShader.glsl", "shaders/textureFragmentShader.glsl");
    const QuadMesh quadMesh{};
    const Renderer renderer(shaderProgram, quadMesh, window);

    const Texture2D texture("assets/pieces_sprite_sheet.png");

    const Texture2DRegion whitePawn(texture, glm::vec2(48, 40), glm::vec2(61, 56));
    const Texture2DRegion all(texture);

    // Render loop
    while (!window.shouldClose())
    {
        // Input
        processInput(window);

        // Rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.drawTextureRegion(whitePawn, glm::vec2(200, 200), 5.0f);
        // renderer.drawTextureRegion(all, glm::vec2(400, 500), 1);

        // Check and call events and swap buffers
        window.swapBuffers();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
