#pragma once

#include <glm/mat4x4.hpp>

/// @brief Like SFML Transformable.
/// @details
/// Defines rotation, scale, origin and rotation.
/// The origin is the origin for all other transformations.
/// The order of transformation is (in local space):
/// first translation (or position), then rotation, then scale.
class Transformable
{
public:
    Transformable();
    virtual ~Transformable() = default;

    const glm::mat4& getTransform() const;

    /// @details
    /// The origin is without any transformation applied. When rendered in the world,
    /// the origin will always be rendered on the world coordinates where the object is rendered.
    /// The default origin is (0, 0).
    const glm::vec2& getOrigin() const;
    void setOrigin(const glm::vec2& origin);

    /// @details
    /// The default position is (0, 0).
    const glm::vec2& getPosition() const;
    void setPosition(const glm::vec2& pos);

    /// @details
    /// The default scale is (1, 1).
    const glm::vec2& getScale() const;
    void setScale(const glm::vec2& scale);

    /// @details
    /// The default rotation is 0.
    /// The unit is in radians, so in counter-clockwise order.
    void setRotation(float rotation);
    float getRotation() const;

private:
    /// @brief Update the matrix based on parameters. Const to allow to be called from getTransform().
    void update() const;

    /// @remarks mutable because, for performance, we recompute the matrix only when it was asked. The matrix is not
    /// updated at each parameter change.
    mutable glm::mat4 m_matrix;
    mutable bool m_needUpdate;

    glm::vec2 m_origin{};
    glm::vec2 m_position{};
    glm::vec2 m_scale{};
    float m_rotation{};
};

