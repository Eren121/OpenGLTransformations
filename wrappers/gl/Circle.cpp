#include "Circle.hpp"
#include <utility/math.hpp>
#include <cmath>

Circle::Circle(unsigned short pointCount)
    : m_radius(1.0f), m_pointCount(pointCount)
{
}

size_t Circle::getVerticesCount() const
{
    return m_pointCount;
}

Vertex Circle::getVertex(int index) const
{
    // angle is in [0;2pi[
    float angle = static_cast<float>(index) / static_cast<float>(m_pointCount) * TAU;

    Vertex v;
    v.pos.x = std::cos(angle) * m_radius;
    v.pos.y = std::sin(angle) * m_radius;

    return v;
}
