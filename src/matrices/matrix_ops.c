#include "main.h"


void		mat4_multiply(mat4 a, mat4 b)
{
	mat4	res;

	for (unsigned int j = 0; j < 4; j++)
		for (unsigned int i = 0; i < 4; i++)
		{
			res[j * 4 + i] = a[j * 4 + 0] * b[0 * 4 + i]
				+ a[j * 4 + 1] * b[1 * 4 + i]
				+ a[j * 4 + 2] * b[2 * 4 + i]
				+ a[j * 4 + 3] * b[3 * 4 + i];
		}
	ft_memcpy(a, res, sizeof(mat4));
}

t_vec3d		mat4_mult_vec(mat4 m, t_vec3d i)
{
	t_vec3d v;

	v.x = i.x * m[0] + i.y * m[1] + i.z * m[2] + i.w * m[3];
	v.y = i.x * m[4] + i.y * m[5] + i.z * m[6] + i.w * m[7];
	v.z = i.x * m[8] + i.y * m[9] + i.z * m[10] + i.w * m[11];
	v.w = i.x * m[12] + i.y * m[13] + i.z * m[14] + i.w * m[15];
	return (v);
}
