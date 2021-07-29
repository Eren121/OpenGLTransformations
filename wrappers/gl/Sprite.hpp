#pragma once

#include "Shape.hpp"

/// @brief A sprite is simply a rectangular shape.
/// @details The rectangle is centered in (0, 0) and has a side length of 1.
class Sprite : public Shape
{
public:
    explicit Sprite(const glm::vec2& size = {1.0f, 1.0f});

    size_t getVerticesCount() const override;
    Vertex getVertex(int index) const override;

private:
    glm::vec2 m_size{1.0f};
    Vertex m_vertices[4];
};

