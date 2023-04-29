#version 460

in vec3 normal;

out vec4 fragmentColor;

void main()
{
    fragmentColor = vec4(normalize(normal) * 0.5 + 0.5, 1.0);
}
