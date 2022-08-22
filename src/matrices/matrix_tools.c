#include "main.h"


void		mat4_identity(mat4 m)
{
	ft_memset(m, 0, sizeof(float) * 16);
	m[0] = 1.0f;
	m[5] = 1.0f;
	m[10] = 1.0f;
	m[15] = 1.0f;
}

void		mat4_scale(mat4 m, float scale)
{
	mat4	s;

	mat4_identity(s);
	m[0] *= scale;
	m[5] *= scale;
	m[10] *= scale;
	mat4_multiply(m, s);
}

void		mat4_translate(mat4 m, float x, float y, float z)
{
	m[3] += x;
	m[7] += y;
	m[11] += z;
}
