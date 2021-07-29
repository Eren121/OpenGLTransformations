#include "VertexArray.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cstddef>

VertexArray::VertexArray() = default;

void VertexArray::setTexture(const Texture *texture)
{
    m_texture = texture;
}

void VertexArray::setVertices(const std::vector<Vertex>& vertices)
{
    m_verticesCount = static_cast<int>(vertices.size());

    auto stride = static_cast<GLsizei>(sizeof(vertices[0]));
    auto nBytes = static_cast<GLsizeiptr>(vertices.size() * stride);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, nBytes, vertices.data(), m_usage);

    glVertexAttribPointer(POSITION, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(offsetof(Vertex, pos)));
    glEnableVertexAttribArray(POSITION);

    glVertexAttribPointer(COLOR, 4, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(offsetof(Vertex, color)));
    glEnableVertexAttribArray(COLOR);

    glVertexAttribPointer(UV, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(offsetof(Vertex, uv)));
    glEnableVertexAttribArray(UV);
}

void VertexArray::setPrimitiveType(GLenum type)
{
    m_primitive = type;
}

void VertexArray::draw(RenderStates states) const
{
    states.model *= getTransform();

    if(states.shader)
    {
        Shader::bind(states.shader);

        states.shader->setUniform("u_Color", glm::vec4{1.0f});
        states.shader->setUniform("u_ModelMatrix", states.model);
        states.shader->setUniform("u_ViewMatrix", states.view);
    }

    Texture::bind(m_texture);

    glBindVertexArray(m_vao);
    glDrawArrays(m_primitive, 0, m_verticesCount);
}

void VertexArray::setUsage(GLenum usage)
{
    m_usage = usage;
}