#pragma once

#include <wrappers/freetype/FTException.hpp>
#include <wrappers/freetype/Glyph.hpp>
#include <wrappers/gl/Texture.hpp>
#include <SDL2/SDL_version.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/vec2.hpp>
#include <filesystem>
#include <map>

/// @file Do not include this file, it is for internal use.

class FontImpl
{
public:
    FontImpl() noexcept(false);
    ~FontImpl() noexcept(false);
    static SDL_version getFreeTypeCompiledVersion();
    SDL_version getFreeTypeLinkedVersion() const;
    void load(const std::filesystem::path& fontPath, int characterSize);
    const Glyph& getGlyph(char c);
    float getLineHeight() const;

private:

    /// @brief Free memory
    void reset();

    static void reverseBitmap(FT_Bitmap& bitmap);

    float m_lineHeight = 0.0f; ///< Font height in pixel.
    FT_Library m_ft = nullptr;
    FT_Face m_face = nullptr;

    std::map<char, Glyph> m_chars;
};

