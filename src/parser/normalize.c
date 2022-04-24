#include "main.h"

enum	e_axis
{
	X * sizeof(float),
	Y * sizeof(float),
	Z * sizeof(float)
};

static unsigned int	dim_max(t_dynarray *vertexs, unsigned char dim)
{
	
}

void				normalize_vertexs(t_env *env)
{
	t_vec3d		*v;
	t_dynarray	*vertexs;

	vertexs = &env->scene.vertexs;
	for (int i = 0; i < vertexs->nb_cells; i++)
	{
		v = dyacc(vertexs, i);
	}
}
