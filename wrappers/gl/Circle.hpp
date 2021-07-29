#pragma once

#include "Shape.hpp"

class Circle : public Shape
{
public:
    Circle(unsigned short pointCount = 30);

    size_t getVerticesCount() const override;
    Vertex getVertex(int index) const override;

private:
    float m_radius;
    unsigned short m_pointCount;
};

