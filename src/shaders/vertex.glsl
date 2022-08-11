#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 mvp;

out vec4 vertexColor;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0) * mvp;
	vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);
}
