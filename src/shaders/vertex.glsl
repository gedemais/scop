#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 mvp;

out vec4 vertexColor;

void main()
{
    //gl_Position = mvp * vec4(aPos, 1.0);
	gl_Position = vec4(aPos, 1.0);
	vertexColor = gl_Position;
}
