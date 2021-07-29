#pragma once

#include "VertexArray.hpp"

class Line : public VertexArray
{
public:
    Line();

    void update(const glm::vec2& a, const glm::vec2& b, const glm::vec4& color = glm::vec4(1.0f), float thickness = 1.0f);

protected:
    std::vector<Vertex> loadVertices() const;

private:
    float m_thickness;
    glm::vec2 m_a;
    glm::vec2 m_b;
    glm::vec4 m_color;
};

