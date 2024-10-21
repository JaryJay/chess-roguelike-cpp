#version 330 core
in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D spriteSheet;
void main()
{
    FragColor = texture(spriteSheet, TexCoord);
}
