#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertexColor;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0) * model * view * projection;
	vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);
}
