#include "Transformable.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>

Transformable::Transformable()
    : m_matrix(1.0f), m_needUpdate(false),
      m_origin(0.0f), m_position(0.0f), m_scale(1.0f), m_rotation(0.0f)
{
}

const glm::mat4& Transformable::getTransform() const
{
    if(m_needUpdate)
    {
        m_needUpdate = false;
        update();
    }
    return m_matrix;
}

const glm::vec2& Transformable::getOrigin() const
{
    return m_origin;
}

const glm::vec2& Transformable::getPosition() const
{
    return m_position;
}

const glm::vec2& Transformable::getScale() const
{
    return m_scale;
}

float Transformable::getRotation() const
{
    return m_rotation;
}

void Transformable::setOrigin(const glm::vec2& origin)
{
    m_origin = origin;
    m_needUpdate = true;
}

void Transformable::setPosition(const glm::vec2& pos)
{
    m_position = pos;
    m_needUpdate = true;
}

void Transformable::setScale(const glm::vec2& scale)
{
    m_scale = scale;
    m_needUpdate = true;
}

void Transformable::setRotation(float rotation)
{
    m_rotation = rotation;
    m_needUpdate = true;
}

void Transformable::update() const
{
    // The Matrix is T*R*S*Tr(-o.x, -o.y), where:
    // T is the translation matrix
    // R is the rotation matrix
    // S is the scale matrix
    // To is the inverse of the origin translation matrix

    // Since we are in 2D, we just compute the transformation in 2D an then cast to 3D
    // To optimize, no need to do in 3D

    glm::mat3 matrix(1.0f);
    matrix = glm::translate(matrix, m_position);
    matrix = glm::rotate(matrix, m_rotation);
    matrix = glm::scale(matrix, m_scale);
    matrix = glm::translate(matrix, -m_origin);

    // Convert 2D transformation to 3D
    // We can't just copy since there is an extra-row and column inside the matrix
    // see https://stackoverflow.com/questions/5508424/convert-2d-affine-transformation-matrix-to-3d-affine-transformation-matrix

    // | a b c |      | a b 0 c |
    // | d e f |  =>  | d e 0 f |
    // | g h i |      | 0 0 1 0 |
    //                | g h 0 i |

    // GLM is column-major
    m_matrix[0] = glm::vec4(matrix[0][0], matrix[0][1], 0.0f, matrix[0][2]);
    m_matrix[1] = glm::vec4(matrix[1][0], matrix[1][1], 0.0f, matrix[1][2]);
    m_matrix[2] = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
    m_matrix[3] = glm::vec4(matrix[2][0], matrix[2][1], 0.0f, matrix[2][2]);
}
