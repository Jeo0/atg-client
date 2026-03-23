#version 460 core
layout (location = 0) in vec3 aaaPos;
layout (location = 1) in vec3 aaaColour;
void main()
{
    gl_Position = vec4(aaaPos.x, aaaPos.y, aaaPos.z, 1.0);
    color = aaaColour;
}
