#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoord;

uniform sampler2D Texture;

void main()
{
	FragColor = texture(Texture, TexCoord);

	//FragColor = vec4(1.0, 1.0, 1.0, 0.0);
}
