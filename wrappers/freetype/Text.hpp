#pragma once

#include <wrappers/gl/Sprite.hpp>
#include <wrappers/gl/Texture.hpp>
#include <wrappers/freetype/Font.hpp>
#include <glm/vec4.hpp>

/// @brief The renderable part of Font, the String itself.
/// @details Wrap a texture of text.
/// @remarks If not scaled, the unit size of the Text is the pixel.
class Text : public Drawable, public Transformable
{
public:
    Text();

    /// @brief Set the font. If the font is null, a draw() call will lead to crash.
    void setFont(const Font *font);
    const Font *getFont() const;

    void setString(const std::string& string);
    const std::string& getString() const;

    void setColor(const glm::vec4& color);
    const glm::vec4& getColor() const;

    void draw(RenderStates states) const override;

    /// @brief Get the size of full text, in pixel.
    glm::vec2 getSize() const;

private:
    /// @brief Update the glyph and the sprite based on the font, string and color.
    void update() const;

    const Font *m_font{nullptr};
    std::string m_string;
    glm::vec4 m_color{glm::vec4(1.0f)};

    mutable std::vector<const Glyph*> m_glyphs; ///< String converted to glyphs
    mutable Sprite m_sprite; ///< Sprite to draw the text
    mutable bool m_needUpdate{true};
    mutable glm::vec2 m_size{0.0f};
};