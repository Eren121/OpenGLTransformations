#version 330 core

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform sampler2D u_Texture;

layout (location = 0) in vec2 in_Pos;
layout (location = 1) in vec4 in_Color;
layout (location = 2) in vec2 in_UV;

out vec4 color;
out vec2 uv;

void main()
{
    vec4 pos = vec4(in_Pos.x, in_Pos.y, 0.0, 1.0);
    gl_Position = u_ViewMatrix * u_ModelMatrix * pos;

    color = in_Color;
    uv = in_UV;
}