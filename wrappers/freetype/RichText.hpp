#pragma once

#include <wrappers/gl/Sprite.hpp>
#include <wrappers/gl/Texture.hpp>
#include <wrappers/freetype/Font.hpp>
#include <glm/vec4.hpp>
#include <variant>

struct RichSegment
{
    struct SegmentIcon
    {
        Texture *texture{nullptr};
        char model; ///< Model for the char size. Only the height is used, the width will be automatic.
    };

    std::variant<SegmentIcon, std::string> data;
};

/// @brief Rich string support
/// @details
/// An API that differs to SFML.
/// Sometimes, you not only need to render text but also need more flexibility : integration styles and icon in texts.
/// That is what this class propose.
/// You can set style to individual characters or segments of text, and insert icons as textures like real character
/// and customize their size. However, it does not define a language like css, you will either have to use this class
/// directly or define your own css-like language.
class RichText : public Drawable, public Transformable
{
public:
    RichText();

    void setFont(const Font *font);
    const Font* getFont() const;

    void draw(RenderStates states) const override;

    /// @details
    /// The font should not not be null.
    void push(const RichSegment& segment);

private:
    void drawString(RenderStates states, glm::vec2& advance, const std::string& str) const;
    void drawIcon(RenderStates states, glm::vec2& advance, const RichSegment::SegmentIcon& icon) const;
    void drawGlyph(RenderStates states, glm::vec2& advance, const Glyph& glyph) const;

    const Font *m_font;
    std::vector<RichSegment> m_segments;

    mutable Sprite m_sprite;
};

