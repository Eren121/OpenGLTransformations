#pragma once

#include <wrappers/gl/Texture.hpp>
#include <glm/vec2.hpp>

struct Glyph
{
    Texture texture; ///< Texture representing the character

    glm::vec2 size; ///< Texture size in pixel, Should be the same as the texture size

    glm::vec2 bearing; ///< Bearing in pixel

    float advance; ///< Advance, in pixel
};

