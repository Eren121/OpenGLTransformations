#pragma once

#include "GL.hpp"
#include <glm/glm.hpp>
#include <string>
#include <filesystem>
#include "Texture.hpp"

/// @brief Represent all necessary for representing OpenGL shaders.
class Shader
{
public:

    /// @brief Try to load a shader.
    /// @param vertex,fragment The source code for each shader.
    /// @throws If there was an error.
    void load(const std::string& vertexSrc, const std::string& fragmentSrc);
    void load(const std::filesystem::path& vert, const std::filesystem::path& frag);

    /// @brief Bind the shader.
    /// @param shader If the shader, the unbind the currently bound shader.
    static void bind(const Shader* shader);
    void bind();


    /// @name
    /// @brief Set a uniform variable
    /// @{

    void setUniform(const std::string& name, const glm::mat4 &value);
    void setUniform(const std::string& name, const glm::vec4& value);
    void setUniform(const std::string& name, int value);

    /// @}

private:

    static void compile(GL::Shader& shader, const std::string& source);

    void link(GL::Shader& vertex, GL::Shader& fragment);

    /// @returns A string containing the compilation information of a shader (vertex or fragment).
    static std::string getShaderInfoLog(GL::Shader& shader);
    static std::string getProgramInfoLog(GL::Program& program);

    GL::Program m_program;
};

