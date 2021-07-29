#pragma once

#include "Vertex.hpp"
#include "Drawable.hpp"
#include "Texture.hpp"
#include "Transformable.hpp"
#include <wrappers/gl/GL.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <type_traits>


static_assert(std::is_standard_layout_v<Vertex>, "Vertex should be standard layout");

class VertexArray : public Drawable, public Transformable
{
public:
    VertexArray();
    virtual ~VertexArray() = default;

    void setTexture(const Texture *texture);

    /// @brief Parameter usage to glBufferData(). Default's to GL_STATIC_DRAW
    /// @see https://www.khronos.org/registry/OpenGL-Refpages/es1.1/xhtml/glBufferData.xml
    /// @remarks The usage will only be updated when the vertices will be reconstructed, that is when the next setVertices() call will be done.
    void setUsage(GLenum usage);

    void draw(RenderStates states) const override;

    /// @brief Each attribute should have it's location as it (type corresponding in Vertex class)
    enum Attribute {
        POSITION = 0,
        COLOR = 1,
        UV = 2,
    };

    void setVertices(const std::vector<Vertex>& vertices);

    /// @param type Should be one of https://www.khronos.org/opengl/wiki/Primitive (GL_TRIANGLES, GL_LINES, etc...)
    void setPrimitiveType(GLenum type);

private:
    GL::VertexArray m_vao;
    GL::Buffer m_vbo;
    GLenum m_primitive = GL_LINES;
    int m_verticesCount = 0;
    const Texture *m_texture = nullptr;
    GLenum m_usage = GL_STATIC_DRAW;
};

