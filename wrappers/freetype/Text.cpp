#include "Text.hpp"
#include <glm/gtc/matrix_transform.hpp>

Text::Text()
{
    // We need the origin of each char to be top left and not center
    // It's because how FreeType handle bearing
    m_sprite.setOrigin({-0.5f, 0.5f});
}

void Text::setFont(const Font *font)
{
    m_font = font;
    m_needUpdate = true;
}

const Font *Text::getFont() const
{
    return m_font;
}

void Text::setString(const std::string& string)
{
    m_string = string;
    m_needUpdate = true;
}

const std::string& Text::getString() const
{
    return m_string;
}

void Text::setColor(const glm::vec4& color)
{
    m_color = color;
    m_sprite.setColor(m_color);
}

const glm::vec4& Text::getColor() const
{
    return m_color;
}

glm::vec2 Text::getSize() const
{
    if(m_needUpdate)
    {
        m_needUpdate = false;
        update();
    }

    return m_size;
}

void Text::update() const
{
    m_glyphs = {};

    if(!m_font)
    {
        m_size = {0.0f, 0.0f};
    }
    else
    {
        glm::vec2 cursor{0.0f, 0.0f};

        for (char c : m_string)
        {
            const Glyph& glyph = m_font->getGlyph(c);
            m_glyphs.push_back(&glyph);

            cursor += glyph.advance;
        }

        // Only one line supported
        cursor.y = m_font->getLineHeight();

        m_size = cursor;
    }
}

void Text::draw(RenderStates states) const
{
    if(m_needUpdate)
    {
        m_needUpdate = false;
        update();
    }

    if(states.shader)
    {
        states.model *= getTransform();

        states.shader->bind();
        states.shader->setUniform("u_Text", true);

        // Cursor in pixel, advance with each letter
        // Bottom-Left of the current character (plus padding)
        glm::vec2 cursor{0.0f, 0.0f};

        for (const Glyph *glyph : m_glyphs)
        {
            m_sprite.setTexture(&glyph->texture);

            // Text rendering is a special case, we don't want to scale to a specific size,
            // but rather render the exact size of the glyph because font, in many cases, is not done to be scaled
            RenderStates states2 = states;
            states2.model = glm::translate(states2.model, {cursor + glyph->bearing, 0.0f});
            states2.model = glm::scale(states2.model, {glyph->size, 1.0f});

            m_sprite.draw(states2);

            cursor.x += glyph->advance;
        }

        // Not used anywhere else so we should release the flag ourselves
        states.shader->setUniform("u_Text", false);
    }
}



