#version 460

in vec3 normal;
in vec2 texCoord;
out vec4 fragmentColor;
uniform sampler2D texture0;

void main()
{
    vec4 textureColor = texture(texture0, vertexTexCoord);
    fragmentColor = vec4(normalize(normal) * 0.5 + 0.5, 1.0) * textureColor;
}
