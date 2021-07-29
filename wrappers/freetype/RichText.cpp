#include "RichText.hpp"
#include <glm/gtc/matrix_transform.hpp>

RichText::RichText()
    : m_font(nullptr)
{
    m_sprite.setOrigin({-0.5f, 0.5f});
}

void RichText::push(const RichSegment& segment)
{
    m_segments.push_back(segment);
}

void RichText::draw(RenderStates states) const
{
    states.model *= getTransform();

    // Cursor in pixel, advance with each letter
    // Bottom-Left of the current character (plus padding)
    glm::vec2 advance{0.0f, 0.0f};

    for(const RichSegment& segment : m_segments)
    {
        switch(segment.data.index())
        {
            case 0:
                // SegmentIcon
                drawIcon(states, advance, std::get<RichSegment::SegmentIcon>(segment.data));
                break;

            case 1:
                // std::string
                drawString(states, advance, std::get<std::string>(segment.data));
                break;
        }
    }
}

void RichText::setFont(const Font *font)
{
    m_font = font;
}

void RichText::drawIcon(RenderStates states, glm::vec2& advance, const RichSegment::SegmentIcon& icon) const
{
    const Glyph& glyph = m_font->getGlyph(icon.model);
    m_sprite.setTexture(icon.texture);

    // gx?
    // gx/gy = tx/ty
    // <=> gx =tx/ty*gy

    glm::vec2 size;
    size.y = glyph.size.y;
    size.x = static_cast<float>(icon.texture->getSize().x) / icon.texture->getSize().y * glyph.size.y;

    states.model = glm::translate(states.model, {advance + glyph.bearing, 0.0f});
    states.model = glm::scale(states.model, {size, 1.0f});

    m_sprite.draw(states);

    // Also add to the offset the difference between the model glyph and the icon glyph size
    advance.x += glyph.advance + (size.x - glyph.size.x);
}

void RichText::drawString(RenderStates states, glm::vec2& advance, const std::string& str) const
{
    for(char c : str)
    {
        const Glyph& glyph = m_font->getGlyph(c);
        m_sprite.setTexture(&glyph.texture);

        drawGlyph(states, advance, glyph);
    }
}

void RichText::drawGlyph(RenderStates states, glm::vec2& advance, const Glyph& glyph) const
{
    // Text rendering is a special case, we don't want to scale to a specific size,
    // but rather render the exact size of the glyph because font, in many cases, is not done to be scaled
    states.model = glm::translate(states.model, {advance + glyph.bearing, 0.0f});
    states.model = glm::scale(states.model, {glyph.size, 1.0f});

    m_sprite.draw(states);

    advance.x += glyph.advance;
}

const Font* RichText::getFont() const
{
    return m_font;
}
