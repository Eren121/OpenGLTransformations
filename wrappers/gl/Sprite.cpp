#include "Sprite.hpp"
#include <utility/Rect.hpp>

Sprite::Sprite(const glm::vec2& size)
    : m_size(size)
{
    Rect posRect;
    posRect.size = m_size;

    Rect texRect;
    texRect.translate(m_size / 2.0f); // Sprite bottom-left is negative but uv bottom-left should be 0.
    texRect.size = m_size;

    Vertex bottomRight;
    bottomRight.pos = posRect.bottomRight();
    bottomRight.uv = texRect.bottomRight();

    Vertex topRight;
    topRight.pos = posRect.topRight();
    topRight.uv = texRect.topRight();

    Vertex topLeft;
    topLeft.pos = posRect.topLeft();
    topLeft.uv = texRect.topLeft();

    Vertex bottomLeft;
    bottomLeft.pos = posRect.bottomLeft();
    bottomLeft.uv = texRect.bottomLeft();

    m_vertices[0] = bottomRight;
    m_vertices[1] = topRight;
    m_vertices[2] = topLeft;
    m_vertices[3] = bottomLeft;
}

size_t Sprite::getVerticesCount() const
{
    return 4;
}

Vertex Sprite::getVertex(int index) const
{
    return m_vertices[index];
}
