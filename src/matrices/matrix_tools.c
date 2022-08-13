#include "main.h"


void		mat4_identity(mat4 m)
{
	ft_memset(m, 0, sizeof(float) * 16);
	m[0] = 1.0f;
	m[5] = 1.0f;
	m[10] = 1.0f;
	m[15] = 1.0f;
}
/*
void		mat4_print(mat4 m)
{
	for (unsigned int i = 0; i < 16; i += 4)
		printf("[ %4f | %4f | %4f | %4f ]\n", (double)m[0 + i], (double)m[1 + i], (double)m[2 + i], (double)m[3 + i]);
}*/

void		mat4_translate(mat4 m, float x, float y, float z)
{
	m[3] += x;
	m[7] += y;
	m[11] += z;
}
