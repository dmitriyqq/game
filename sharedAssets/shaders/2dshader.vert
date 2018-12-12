#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 uv;

void main()
{
    gl_Position =  projection * view * model * vec4(aPos, 0.0, 1.0);
    uv = aUV;
    // gl_Position = projection * view * vec4(aPos, 1.0);
}
