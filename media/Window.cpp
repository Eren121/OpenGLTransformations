#include "Window.hpp"
#include "utility/Str.hpp"
#include <GL/glew.h>
#include <iostream>

Window::Window(const std::string& title, int width, int height)
    : m_input(*this)
{
    setupGLAttributes();
    createWindow(title, width, height);
    createContext();

    // GLEW should be initialized after creating the window context!!!
    initGLEW();
}

Window::~Window()
{
    SDL_DestroyWindow(m_window), m_window = nullptr;
    SDL_GL_DeleteContext(m_context), m_context = nullptr;
}

void Window::createWindow(const std::string& title, int width, int height)
{
    int x = SDL_WINDOWPOS_CENTERED;
    int y = SDL_WINDOWPOS_CENTERED;
    m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    if(!m_window)
    {
        throw SDL::Exception("Failed to create the window");
    }

    m_running = true;
}

void Window::createContext()
{
    m_context = SDL_GL_CreateContext(m_window);
    if(!m_context)
    {
        throw SDL::Exception("Failed to create an OpenGL context inside the window");
    }

    // We will need blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    printGPUInfo();
}

void Window::initGLEW()
{
    glewExperimental = true;
    GLenum err = glewInit();

    if(err != GLEW_OK)
    {
        throw Exception(Str{} << "Glew initialization failed: " << glewGetErrorString(err));
    }
}

void Window::setupGLAttributes()
{
    // OpenGL version
    int major = 3;
    int minor = 3;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);;
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // version 3.1 core
}

bool Window::isOpen() const
{
    return m_running;
}

void Window::handleEvents()
{
    // Process all pending events in the event queue leaving the queue empty
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
        switch(e.type)
        {
            case SDL_QUIT:
                m_running = false;
                break;
        }

        onEvent(e);
    }
}

void Window::display()
{
    onUpdate();

    SDL_GL_SwapWindow(m_window);
}

glm::vec2 Window::getSize() const
{
    int w, h;

    // May be different from SDL_GetWindowSize(), see https://wiki.libsdl.org/SDL_GetWindowSize
    SDL_GL_GetDrawableSize(m_window, &w, &h);

    return {w, h};
}

UnifiedInput& Window::getInput()
{
    return m_input;
}

const UnifiedInput& Window::getInput() const
{
    return m_input;
}

void Window::printGPUInfo()
{
    // Print some info

    int maxTexSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
    std::cout << "Max. texture size: " << maxTexSize << "x" << maxTexSize << std::endl;

}

SDL_Window *Window::getHandle() const
{
    return m_window;
}
