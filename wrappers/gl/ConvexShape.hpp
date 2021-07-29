#pragma once

#include "Shape.hpp"

/// @brief Convex Shape.
/// @details In details, the only difference between Shape is ConvexShape is that ConvexShape has public writable
/// vertices. But, in theory, Shape is also convex. This simple naming convention is better, has the user does not
/// need to know the Shape is concave because he will use child classes. This is somehow a different convention
/// from SFML: sf::ConvexShape == Shape, sf::VertexArray = ConvexShape.
/// @remarks
/// If the shape is not filled or rendered with GL_LINES or GL_POINTS, then the shape can be not convex.
class ConvexShape : public Shape
{
public:
    std::size_t getVerticesCount() const override;
    Vertex getVertex(int index) const override;

    void setVerticesCount(std::size_t count);
    void setVertex(int index, const Vertex& vertex);

private:
    std::vector<Vertex> m_vertices;
};

