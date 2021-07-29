#pragma once

#include "wrappers/nostd/source_location.hpp"
#include "utility/Exception.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/vec4.hpp>
#include <string>

/// @brief SDL wrapper and utility functions
namespace SDL
{
    /// @brief Deleter for SDL structures
    struct deleter
    {
        void operator()(SDL_Window *window);
    };

    /// @brief Exception to throw when an SDL error is met.
        class Exception : public ::Exception
        {
        public:
            explicit Exception(const std::string& msg = "", const nostd::source_location& loc = nostd::source_location::current());
        };

    /// @brief Exception to throw when a SDL_image error is met.
    class IMGException : public ::Exception
    {
    public:
        explicit IMGException(const std::string& msg = "", const nostd::source_location& loc = nostd::source_location::current());
    };

    /// @returns The SDL version in the form "X.Y.Z" where X is major, Y is minor and Z is patch.
    std::string to_string(const SDL_version& version);

    /// @brief Initialize all needed components for SDL.
    /// @details Will also log the SDL Version, and register atexit handlers SDL_Quit.
    void init();

    /// @brief Initialize SDL_image and register atexit handler IMG_Quit().
    void init_image();

    /// @brief Print both compiled and linked version (which can be different is SDL is a linked dynamically) on standard output.
    /// @details Follow the conventions of each SDL library extension (SDL, SDL_image, SDL_ttf).
    /// Extensions use the same structure SDL_Version to store a version.
    /// @remarks Can safely be called before SDL_Init()
    void printVersion(const char *libName, const SDL_version& compiled, const SDL_version& linked);

    /// @brief Flip vertically the pixels, useful to convert to OpenGL texture.
    void flip_vertically(SDL_Surface* surface);


    /// @name
    /// @brief Some conversions functions from/to GLM
    /// @{

    SDL_Color colorFromGLM(const glm::vec4& c);
    glm::vec4 colorToGLM(const SDL_Color& c);

    /// @}
}