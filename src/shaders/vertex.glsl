#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model_view_projection;

out vec4 vertexColor;

void main()
{
    gl_Position = model_view_projection * vec4(aPos, 1.0);
	vertexColor = gl_Position;
}
