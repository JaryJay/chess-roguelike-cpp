#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec2 aOffset;

out vec2 TexCoord;

void main()
{
    TexCoord = aTexCoord;
    vec3 pos = aPos + vec3(aOffset, 0.0);
    gl_Position = vec4(pos, 1.0);
}
