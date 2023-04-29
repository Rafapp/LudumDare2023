#version 460
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;

void main(){
    normal = normalize(vec3(model * vec4(vertexNormal, 0.0)));
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
}