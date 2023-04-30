#version 460
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexCoord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec2 texCoord;

void main(){
    normal = normalize(vec3(model * vec4(vertexNormal, 0.0)));
    texCoord = vertexTexCoord;
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
}