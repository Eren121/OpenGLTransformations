#include "Vertex.hpp"
#include "GL.hpp"

void Vertex::vertexAttribPointer()
{
    GL::vertexAttribPointer(Vertex::Position, 2, GL_FLOAT, &Vertex::pos);
    GL::vertexAttribPointer(Vertex::Color, 4, GL_FLOAT, &Vertex::color);
    GL::vertexAttribPointer(Vertex::TexCoords, 2, GL_FLOAT, &Vertex::uv);
}
