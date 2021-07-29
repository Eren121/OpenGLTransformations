#version 330 core

uniform sampler2D u_Texture;
uniform vec4 u_Color;
uniform bool u_Text = false;

in vec4 color; // Global color
in vec2 uv;

out vec4 out_Color;

void main()
{
    // 1 if text is rendered, 0 otherwise
    float isText = float(u_Text);

    vec4 textureColor;
    textureColor = mix(texture(u_Texture, uv), vec4(vec3(1.0), texture(u_Texture, uv).r), isText);

    out_Color = u_Color * color * textureColor;
}