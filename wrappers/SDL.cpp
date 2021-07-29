#include "SDL.hpp"
#include "utility/Str.hpp"
#include <iostream>

void SDL::deleter::operator()(SDL_Window *window)
{
    SDL_DestroyWindow(window);
}

void SDL::init()
{
    atexit(SDL_Quit);

    SDL_version compiled, linked;
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    printVersion("SDL", compiled, linked);

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw SDL::Exception("Failed to initialized SDL with requested flags");
    }
}

void SDL::init_image()
{
    atexit(IMG_Quit);

    SDL_version compiled;
    const SDL_version *linked = IMG_Linked_Version();
    SDL_IMAGE_VERSION(&compiled);
    printVersion("SDL_image", compiled, *linked);

    // Init SDL_image with PNG loading
    int initFlags = IMG_INIT_PNG;

    // IMG_Init returns the flags that were successfully initialized
    // We required to successfully initialize all flags asked
    if((IMG_Init(initFlags) & initFlags) != initFlags)
    {
        throw SDL::IMGException("Failed to initialized SDL_image with requested flags");
    }
}

std::string SDL::to_string(const SDL_version& version)
{
    std::ostringstream ss;
    ss << static_cast<int>(version.major);
    ss << "." << static_cast<int>(version.minor);
    ss << "." << static_cast<int>(version.patch);

    return ss.str();
}

void SDL::printVersion(const char *libName, const SDL_version& compiled, const SDL_version& linked)
{
    // Mainly copied from https://wiki.libsdl.org/SDL_GetVersion
    // The compiled version and the linked version may be different if SDL is linked dynamically

    std::cout << libName << " compiled version: " << to_string(compiled) << std::endl;
    std::cout << libName << " linked version: " << to_string(linked) << std::endl;
}

void SDL::flip_vertically(SDL_Surface *surface)
{
    // From https://stackoverflow.com/questions/65815332/flipping-a-surface-vertically-in-sdl2

    SDL_LockSurface(surface);

    int pitch = surface->pitch; // row size
    char* temp = new char[pitch]; // intermediate buffer
    char* pixels = (char*) surface->pixels;

    for(int i = 0; i < surface->h / 2; ++i) {
        // get pointers to the two rows to swap
        char* row1 = pixels + i * pitch;
        char* row2 = pixels + (surface->h - i - 1) * pitch;

        // swap rows
        memcpy(temp, row1, pitch);
        memcpy(row1, row2, pitch);
        memcpy(row2, temp, pitch);
    }

    delete[] temp;

    SDL_UnlockSurface(surface);
}

SDL_Color SDL::colorFromGLM(const glm::vec4& c)
{
    SDL_Color ret;
    ret.r = static_cast<Uint8>(c.r * 255.0f);
    ret.g = static_cast<Uint8>(c.g * 255.0f);
    ret.b = static_cast<Uint8>(c.b * 255.0f);
    ret.a = static_cast<Uint8>(c.a * 255.0f);
    return ret;
}

glm::vec4 SDL::colorToGLM(const SDL_Color& c)
{
    glm::vec4 ret{c.r, c.g, c.b, c.a};
    ret /= 255.0f;
    return ret;
}

SDL::Exception::Exception(const std::string& msg, const nostd::source_location& loc)
    : ::Exception(Str{} << msg << ". SDL error: " << SDL_GetError(), loc)
{
}

SDL::IMGException::IMGException(const std::string& msg, const nostd::source_location& loc)
    : Exception(Str{} << msg << ". SDL_image error: " << IMG_GetError(), loc)
{
}
