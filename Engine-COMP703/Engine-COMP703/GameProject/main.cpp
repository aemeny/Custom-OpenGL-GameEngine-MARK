#include "../Graphics/GraphicsMasterHeader.h"
#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>
#include <iostream>

#undef main
int main()
{
    SDL_Window* window;
    SDL_GLContext context;

    // Window Initialise
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error("Failed to initialize SDL");
    }
    if (!(window = SDL_CreateWindow("WINDOW", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        900, 900, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)))
    {
        SDL_Quit();
        throw std::runtime_error("Failed to create Window");
    }
    if (!(context = SDL_GL_CreateContext(window)))
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("Failed to create OpenGL context");
    }

    // Init glew
    glewInit();

    std::shared_ptr<GraphicsRenderer::ModelHandler> model = 
        std::make_shared<GraphicsRenderer::ModelHandler>("../Samples/Models/Curuthers/Curuthers.obj");

    std::shared_ptr<GraphicsRenderer::ShaderHandler> shader = 
        std::make_shared<GraphicsRenderer::ShaderHandler>("../Shaders/Perspective/VertexShader.txt", "../Shaders/Perspective/FragmentShader.txt");

    std::shared_ptr<GraphicsRenderer::TextureHandler> texture =
        std::make_shared<GraphicsRenderer::TextureHandler>("../Samples/Textures/Curuthers/Curuthers.png");

    glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)(900 / 900), 0.01f, 100.0f);

    while (true)
    {
        //Clear depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //draw background
        glClearColor(0.42f, 0.5f, 0.68f, 1.0f);

        shader->bindShader(projection, "u_Projection");
        shader->renderModel(model, texture);

        //Swap window
        SDL_GL_SwapWindow(window);
    }

    if (context)
    {
        std::cout << "SDL_GL_DeleteContext\n" << std::endl;
        SDL_GL_DeleteContext(context);
    }
    if (window)
    {
        std::cout << "SDL_DestroyWindow\n" << std::endl;
        SDL_DestroyWindow(window);

        std::cout << "SDL_Quit\n" << std::endl;
        SDL_Quit();
    }

    return 0;
}