#pragma once

#include "RenderStates.hpp"

class Drawable
{
public:
    virtual ~Drawable() = default;

    virtual void draw(RenderStates states) const = 0;
};

