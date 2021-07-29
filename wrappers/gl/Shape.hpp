#pragma once

#include "Drawable.hpp"
#include "Texture.hpp"
#include "Transformable.hpp"
#include "Vertex.hpp"
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include <vector>

/// @brief Basic Shape.
/// @details
/// It serves as a base for the other graphical shapes.
/// It does not define the vertices, but rather can generate all the OpenGL from the vertices.
/// It automatically generates the OpenGL buffers, including outlines.
/// To make your own Shapes, use rather ConvexShape than Shape for a simple reason: we need all the Shape to derive
/// from this class, but we don't want to make the vertices of these classes to be editable by the user.
/// So the class Shape does only define getters. The ConvexShape is just a Shape implementation with setters.
/// We consider the shape to always be centered in zero. This assumption is used to generate the outline, by
/// scaling by the outline thickness, and texture UVs.
/// For texturing, the coordinates are mapped from clip space to uv space.
/// That means the vertice coordinate (-1, -1) is uv (0, 0) and the vertice coordinate (1, 1) is uv (1, 1).
/// Every setter modify the internal state of the Shape, OpenGL buffers should be recomputed, that can be costly
/// if the shape is big.
class Shape : public Transformable, public Drawable
{
public:
    /// @brief Draw the shape.
    /// @details Recompute the vertices if the Shape was modified.
    void draw(RenderStates states = {}) const override;

    void setTexture(const Texture *texture);
    const Texture* getTexture() const;

    /// @brief Get the fill color.
    /// @details Opaque White by default.
    const glm::vec4& getColor() const;
    void setColor(const glm::vec4& color);

    /// @brief Get the outline color.
    /// @details Opaque White by default.
    const glm::vec4& getOutlineColor() const;
    void setOutlineColor(const glm::vec4& color);

    /// @brief Get the outline thickness.
    /// @details Zero by default. Set to Zero to disable the outline.
    /// The outline has no texture, only an uniform color.
    float getOutlineThickness() const;
    void setOutlineThickness(float thickness);

    /// @brief Get if the Shape is dynamic.
    /// @details For optimization.
    /// A Shape is considered dynamic if its parameters are changed often. The default is false.
    /// It translates to the usage parameter of glBufferData().
    void setDynamic(bool dynamic);
    bool isDynamic() const;

    /// @brief Set the count of vertices of the Shape. Every vertice should be accessible by getVertice(i),
    /// for 0 <= i < getVerticesCount().
    /// @details To be overriden by the child class. No setter is provided to protected from that,
    /// for example if the child class is a Circle,
    /// the user cannot change the geometry to something that is not a Circle.
    virtual std::size_t getVerticesCount() const = 0;

    /// @brief Get individual vertice of the shape.
    /// @detaisl If the color of the Vertex is not opaque white, it will be multiplied with the color of the shape,
    /// depending if it is outline or fill color.
    virtual Vertex getVertex(int index) const = 0;

    /// @brief Get all the vertices of the shape.
    /// @details The vertices should form a concave shape, otherwise the shape will not be goodly rendered.
    std::vector<Vertex> getVertices() const;

    /// @brief Get all the outline vertices of the shape.
    /// @details The outline vertices are defined as the border of the outline that is not the fill border.
    /// If there is not outline, this will return the same as getVertices().
    std::vector<Vertex> getOutlineVertices() const;

protected:
    void needUpdate();

private:
    static glm::vec2 getCenterOfMass(const std::vector<Vertex>& polygon);

    GLenum getUsage() const;

    void update() const;
    void updateOutline() const;

    const Texture *m_texture{nullptr};

    glm::vec4 m_fillColor{1.0f};

    glm::vec4 m_outlineColor{1.0f};
    float m_outlineThickness{0.0f};

    mutable bool m_needUpdate{true}; // True by default, so that if the Shape is never drawn no GPU memory will be used.
    // Also children class constructor may need to be updated

    GL::VertexArray m_vao; // Fill shape buffer
    GL::Buffer m_vbo;

    GL::VertexArray m_outlineVao; // Outline shape buffer
    GL::Buffer m_outlineVbo;

    bool m_dynamic{false};
};

