#version 460 core
in vec3 iColour;
out vec4 oFragColor;
void main()
{
    FragColor = vec4(iColour, 1.0f);
}
