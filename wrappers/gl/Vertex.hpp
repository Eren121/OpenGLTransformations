#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

struct Vertex
{
    /// @brief Each attribute should have it's location as it
    enum Attribute {
        Position = 0, ///< pos
        Color = 1, ///< color
        TexCoords = 2, ///< uv
    };

    Vertex() = default;
    Vertex(const glm::vec2& pos) : pos(pos) {}
    Vertex(const glm::vec2& pos, const glm::vec4& color) : pos(pos), color(color) {}

    glm::vec2 pos{0.0f};
    glm::vec4 color{1.0f};
    glm::vec2 uv{0.0f};

    /// @brief Setup the attributes with glVertexAttribPointer() for the currently bound VAO.
    static void vertexAttribPointer();
};
