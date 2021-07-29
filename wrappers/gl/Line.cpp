
#include "Line.hpp"

Line::Line()
    : m_a(), m_b(), m_color(), m_thickness()
{
}

std::vector<Vertex> Line::loadVertices() const
{
    std::vector<Vertex> vertices;
    Vertex v;
    v.color = m_color;

    v.pos = m_a;
    vertices.push_back(v);

    v.pos = m_b;
    vertices.push_back(v);

    return vertices;
}

void Line::update(const glm::vec2& a, const glm::vec2& b, const glm::vec4& color, float thickness)
{
    m_a = a;
    m_b = b;
    m_color = color;
    m_thickness = thickness;

    setVertices(loadVertices());
    setPrimitiveType(GL_LINE_STRIP);
}
