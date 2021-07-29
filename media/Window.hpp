#pragma once

#include "input/UnifiedInput.hpp"
#include <wrappers/SDL.hpp>
#include <wrappers/gl/Texture.hpp>
#include <sigslot/signal.hpp>
#include <glm/glm.hpp>
#include <string>

/// @brief Window instance.
class Window
{
public:
    Window(const std::string& title, int width, int height);

    /// @brief Deletes the window and the OpenGL context
    ~Window();

    /// @returns False when user want to quit the window (ALT+F4, icon, etc...).
    bool isOpen() const;

    /// @brief Handle the window events.
    void handleEvents();

    /// @brief Render the window by swapping OpenGL buffers.
    void display();

    /// @brief Get the size of the window in pixel.
    glm::vec2 getSize() const;

    UnifiedInput& getInput();
    const UnifiedInput& getInput() const;

    SDL_Window* getHandle() const;

private:
    /// @brief Setup the options for OpenGL.
    void setupGLAttributes();

    /// @brief Creates the window
    void createWindow(const std::string& title, int width, int height);

    /// @brief Creates the OpenGL context
    void createContext();

    /// @brief Initialize GLEW (should be called after having created the OpenGL context)
    void initGLEW();

    SDL_Window *m_window;
    SDL_GLContext m_context;
    bool m_running;

public:
    /// @brief Called when each event is intercepted.
    sigslot::signal<const SDL_Event&> onEvent;

    /// @brief Called at each frame.
    sigslot::signal<> onUpdate;

private:
    void printGPUInfo();

    UnifiedInput m_input;
};

