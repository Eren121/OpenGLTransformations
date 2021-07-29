#pragma once

#include <glm/glm.hpp>

template<typename T>
struct tRect
{
    using vec = glm::tvec2<T>;

    tRect(const vec& size = {0, 0}, const vec& center = {0, 0})
        : size(size), center(center)
    {
    }

    vec size;
    vec center;

    T left() const
    {
        return center.x - size.x / 2.0f;
    }

    T right() const
    {
        return center.x + size.x / 2.0f;
    }

    T top() const
    {
        return center.y + size.y / 2.0f;
    }

    T bottom() const
    {
        return center.y - size.y / 2.0f;
    }

    vec bottomLeft() const
    {
        return center - size / static_cast<T>(2);
    }

    vec bottomRight() const
    {
        return {center.x + size.x / 2.0f, center.y - size.y / 2.0f};
    }

    vec topLeft() const
    {
        return {center.x - size.x / 2.0f, center.y + size.y / 2.0f};
    }

    vec topRight() const
    {
        return center + size / static_cast<T>(2);
    }

    void translate(const glm::vec2& amount)
    {
        center += amount;
    }
};

using Rect = tRect<float>;