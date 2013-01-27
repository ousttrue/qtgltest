#version 400

layout(location=0) in vec3 VertexPosition;
layout(location=1) in vec3 VertexNormal;
layout(location=2) in vec3 VertexColor;

out vec3 Color;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;

void main()
{
    Color=VertexColor;
    gl_Position=ProjectionMatrix * ViewMatrix * vec4(VertexPosition, 1.0);
}

