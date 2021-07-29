#pragma once

#include "Shader.hpp"
#include <glm/glm.hpp>

struct RenderStates
{
    Shader *shader{nullptr};

    glm::mat4 view{1.0f};
    glm::mat4 model{1.0f};
};

