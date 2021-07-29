
#include "ConvexShape.hpp"

size_t ConvexShape::getVerticesCount() const
{
    return m_vertices.size();
}

Vertex ConvexShape::getVertex(int index) const
{
    return m_vertices[index];
}

void ConvexShape::setVerticesCount(std::size_t count)
{
    m_vertices.resize(count);
    needUpdate();
}

void ConvexShape::setVertex(int index, const Vertex& vertex)
{
    m_vertices[index] = vertex;
    needUpdate();
}
