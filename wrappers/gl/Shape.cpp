#include "Shape.hpp"
#include <cstddef>

void Shape::setTexture(const Texture *texture)
{
    m_texture = texture;
}

const Texture* Shape::getTexture() const
{
    return m_texture;
}

const glm::vec4& Shape::getColor() const
{
    return m_fillColor;
}

void Shape::setColor(const glm::vec4& color)
{
    m_fillColor = color;
    // No need to update, the fill color is managed in the shader
}

const glm::vec4& Shape::getOutlineColor() const
{
    return m_outlineColor;
}

void Shape::setOutlineColor(const glm::vec4& color)
{
    m_outlineColor = color;
    // No need to update, the outline color is managed in the shader
}

float Shape::getOutlineThickness() const
{
    return m_outlineThickness;
}

void Shape::setOutlineThickness(float thickness)
{
    if(m_outlineThickness != thickness)
    {
        m_outlineThickness = thickness;
        needUpdate();
    }
}

void Shape::draw(RenderStates states) const
{
    if(m_needUpdate)
    {
        m_needUpdate = false;
        update();
    }

    if(states.shader)
    {
        states.model *= getTransform();

        Shader::bind(states.shader);
        Texture::bind(m_texture);

        states.shader->setUniform("u_ModelMatrix", states.model);
        states.shader->setUniform("u_ViewMatrix", states.view);

        const auto count = static_cast<GLsizei>(getVerticesCount());

        if(count >= 2) // Prevent crash for empty shapes
        {
            // Draw fill
            states.shader->setUniform("u_Color", m_fillColor);
            glBindVertexArray(m_vao);

            if(count == 2)
            {
                // Cannot draw triangles with 2 vertices...
                // Assume it is a line in this case
                glDrawArrays(GL_LINES, 0, count);
            }
            else
            {
                glDrawArrays(GL_TRIANGLE_FAN, 0, count);
            }

            // Draw outline if there is one
            if (m_outlineThickness != 0.0f && count > 2)
            {
                states.shader->setUniform("u_Color", m_outlineColor);
                glBindVertexArray(m_outlineVao);

                // + 1 because we need to close the shape>
                glDrawArrays(GL_TRIANGLE_STRIP, 0, (count + 1) * 2);
            }
        }
    }
}

void Shape::update() const
{
    std::vector<Vertex> vertices = getVertices();

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    GL::bufferData(GL_ARRAY_BUFFER, vertices, getUsage());
    Vertex::vertexAttribPointer();

    updateOutline();
}

void Shape::updateOutline() const
{
    std::vector<Vertex> vertices;

    if(m_outlineThickness != 0.0f && getVerticesCount() > 2)
    {
        auto innerVertices = getVertices();
        auto outerVertices = getOutlineVertices();

        // The ouline border have no color (Vertices color is white, and the color of the shader)
        for(Vertex& v : innerVertices)
        {
            v.color = glm::vec4{1.0f};
        }

        assert(innerVertices.size() == outerVertices.size());
        const std::size_t size = innerVertices.size();

        // It will be rendered in order, so we need to intermix them
        vertices.reserve(2 * size);
        for(std::size_t i = 0; i < size; ++i)
        {
            vertices.push_back(innerVertices[i]);
            vertices.push_back(outerVertices[i]);
        }

        // Close the shape
        vertices.push_back(innerVertices[0]);
        vertices.push_back(outerVertices[0]);
    }

    glBindVertexArray(m_outlineVao);
    glBindBuffer(GL_ARRAY_BUFFER, m_outlineVbo);

    GL::bufferData(GL_ARRAY_BUFFER, vertices, getUsage());
    Vertex::vertexAttribPointer();
}

void Shape::setDynamic(bool dynamic)
{
    if(m_dynamic != dynamic)
    {
        m_dynamic = dynamic;
        needUpdate();
    }
}

bool Shape::isDynamic() const
{
    return m_dynamic;
}

std::vector<Vertex> Shape::getVertices() const
{
    auto count = static_cast<std::size_t>(getVerticesCount());

    std::vector<Vertex> ret;
    ret.reserve(count);

    for(int i = 0; i < count; ++i)
    {
        ret.emplace_back(getVertex(i));
    }

    return ret;
}

std::vector<Vertex> Shape::getOutlineVertices() const
{
    std::vector<Vertex> vertices = getVertices();
    std::vector<Vertex> outlines;

    if(vertices.size() > 2)
    {
        outlines.reserve(vertices.size());

        const auto count = vertices.size();
        for(std::size_t k = 0; k < count; ++k)
        {
            const std::size_t kk = k + count; // Ensure in range of vertices with modulo (taking the previous and next vertices)
            const glm::vec2& a = vertices[(kk - 1) % count].pos;
            const glm::vec2& b = vertices[kk % count].pos;
            const glm::vec2& c = vertices[(kk + 1) % count].pos;

            const glm::vec2 ab = glm::normalize(b - a);
            const glm::vec2 bc = glm::normalize(c - b);

            const glm::vec2 nab {ab.y, -ab.x};
            const glm::vec2 nbc {bc.y, -bc.x};

            const float cosx = glm::dot(nab, nbc);

            const float x = std::acos(cosx);

            // Tan=Opp/adj
            const float y = std::tan(x / 2.0f) * m_outlineThickness;

            Vertex outline;
            outline.pos = b + nab * m_outlineThickness + ab * y;

            //outline.pos = b + nab * m_outlineThickness;
            outlines.push_back(outline);
        }
    }

    return outlines;
}

GLenum Shape::getUsage() const
{
    return m_dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
}

void Shape::needUpdate()
{
    m_needUpdate = true;
}

glm::vec2 Shape::getCenterOfMass(const std::vector<Vertex>& polygon)
{
    glm::vec2 center{0.0f, 0.0f};

    for(const Vertex& vertex : polygon)
    {
        center += vertex.pos;
    }

    center /= polygon.size();
    return center;
}
