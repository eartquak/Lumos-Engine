#version 400 core

layout(location=0) in vec2 vertexPos;
layout(location=1) in vec3 vertexColor;

out vec3 fragmentColor;

uniform float time;

void main() {
    float angle = time * 3.14159 * 0.1; // Full rotation in 1 second

    // Rotate the vertex position around the origin
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);
    mat2 rotationMatrix = mat2(cosAngle, -sinAngle, sinAngle, cosAngle);
    vec2 rotatedVertexPos = rotationMatrix * vertexPos;
    gl_Position = vec4(rotatedVertexPos, 0.0, 1.0);
    fragmentColor = vertexColor;
}