#include "GL.hpp"
#include <utility/Exception.hpp>
#include <cstdio>
#include <cassert>

GL::Shader::Shader(GLenum type)
{
    assert(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER || type == GL_GEOMETRY_SHADER);

    id = glCreateShader(type);
    if(!id)
    {
        throw Exception("Failed to create a shader");
    }
}

GL::Shader::~Shader()
{
    glDeleteShader(id);
    id = 0;
}

GL::Program::Program()
{
    id = glCreateProgram();
    if(!id)
    {
        throw Exception("Failed to create a shader program");
    }
}

GL::Program::~Program()
{
    glDeleteProgram(id);
    id = 0;
}

GL::Buffer::Buffer()
{
    glGenBuffers(1, &id);
}

GL::Buffer::~Buffer()
{
    glDeleteBuffers(1, &id);
}

GL::VertexArray::VertexArray()
{
    glGenVertexArrays(1, &id);
}

GL::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &id);
}

GL::Texture::Texture()
{
    glGenTextures(1, &id);
}

GL::Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

namespace GL
{
    namespace
    {
        bool throwOnError;

        /// @brief Callback for OpenGL error
        void GLAPIENTRY
        onError(GLenum source,
              GLenum type,
              GLuint id,
              GLenum severity,
              GLsizei length,
              const GLchar *message,
              const void *userParam)
        {

            if(throwOnError && type == GL_DEBUG_TYPE_ERROR)
            {
                // Only print if error

                fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
                        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
                        type, severity, message);

                // Throw if the message is an error and throwing is enabled
                throw Exception("GL Error");
            }
        }
    }
}

void GL::enableDebugging(bool throwOnError)
{
    GL::throwOnError = throwOnError;

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GL::onError, 0);
}
