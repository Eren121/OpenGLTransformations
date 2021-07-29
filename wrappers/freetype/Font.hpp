#pragma once

#include <wrappers/freetype/Glyph.hpp>
#include <filesystem>
#include <memory>
#include <SDL2/SDL_version.h>

/// @brief Freetype wrappers, also GL wrappers.
/// @details Renderable freetype font in OpenGL.
class Font
{
public:
    Font();
    ~Font();

    /// @brief Get the glyph.
    /// @details Load it if it does not exists yet.
    const Glyph& getGlyph(char c) const;

    /// @param fontPath The path of the .ttf font file.
    /// @param characterSize Size of the font (in point, not pixels).
    void load(const std::filesystem::path& fontPath, int characterSize);

    /// @brief Get the size of line, in pixel.
    float getLineHeight() const;

    /// @brief Get the version of freetype.
    /// @returns The FreeType version. We use a SDL_version structure to store the version because it has the same fields.
    static SDL_version getFreeTypeCompiledVersion();
    SDL_version getFreeTypeLinkedVersion() const;

private:
    std::unique_ptr<class FontImpl> m_impl;  ///< The actual implementation. We don't include the header to make faster compilation time.

    friend class Text;
};

