#include "Shader.hpp"
#include <utility/Exception.hpp>
#include <utility/IO.hpp>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

void Shader::load(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    GL::Shader vert(GL_VERTEX_SHADER);
    GL::Shader frag(GL_FRAGMENT_SHADER);

    compile(vert, vertexSrc);
    compile(frag, fragmentSrc);
    link(vert, frag);

    // At the end of the scope the GL::Shader will be deleted,
    // it's fine because they are no more necessary
}

void Shader::load(const std::filesystem::path& vert, const std::filesystem::path& frag)
{
    load(IO::readAll(vert), IO::readAll(frag));
}

std::string Shader::getProgramInfoLog(GL::Program& programID)
{
    int len; // Count of characters in the log message (including null-terminating char)
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &len);

    std::vector<char> log(len, '\0');
    glGetProgramInfoLog(programID, len, nullptr, &log[0]);

    return std::string{log.begin(), log.end()};
}

std::string Shader::getShaderInfoLog(GL::Shader& shaderID)
{
    int len; // Count of characters in the log message (including null-terminating char)
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &len);

    std::vector<char> log(len, '\0');
    glGetShaderInfoLog(shaderID, len, nullptr, &log[0]);

    return std::string{log.begin(), log.end()};
}

void Shader::compile(GL::Shader& shader, const std::string& source)
{
    const char* c_source = source.c_str();
    glShaderSource(shader, 1, &c_source, nullptr); // The source is not compiled, just copied into the shader object at this time

    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(!status)
    {
        throw Exception(getShaderInfoLog(shader));
    }
}

void Shader::link(GL::Shader& vertex, GL::Shader& fragment)
{
    glAttachShader(m_program, vertex);
    glAttachShader(m_program, fragment);
    glLinkProgram(m_program);

    int success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if(!success)
    {
        throw Exception(getProgramInfoLog(m_program));
    }

    // The shaders are not needed anymore
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::bind(const Shader *shader)
{
    if(shader)
    {
        glUseProgram(shader->m_program);
    }
    else
    {
        glUseProgram(0);
    }
}

void Shader::bind()
{
    bind(this);
}

void Shader::setUniform(const std::string& name, const glm::mat4& value)
{
    bind();
    glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniform(const std::string& name, int value)
{
    bind();
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}

void Shader::setUniform(const std::string& name, const glm::vec4& value)
{
    bind();
    glUniform4fv(glGetUniformLocation(m_program, name.c_str()), 1, glm::value_ptr(value));
}
