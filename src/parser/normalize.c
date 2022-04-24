#include "main.h"

enum	e_axis
{
	X,
	Y,
	Z
};

static void	dim_min_max(t_dynarray *vertexs, size_t dim, float *min, float *max)
{
	float	*comp;

	*min = FLT_MAX;
	*max = FLT_MIN;
	for (int i = 0; i < vertexs->nb_cells; i++)
	{
		comp = (float*)dyacc(vertexs, i);

		if (comp[dim] < *min)
			*min = comp[dim];
		else if (comp[dim] > *max)
			*max = comp[dim];
	}
}

static void			normalize_dim(t_dynarray *vertexs, size_t dim, float min, float max)
{
	float	*comp;

	for (int i = 0; i < vertexs->nb_cells; i++)
	{
		comp = (float*)dyacc(vertexs, i);
		comp[dim] = (((comp[dim] - min) * (1.0f - -1.0f)) / (max - min)) + -1.0f;
	}
}

void				normalize_vertexs(t_env *env)
{
	t_dynarray	*vertexs;
	float		mins[3];
	float		maxs[3];

	vertexs = &env->scene.vertexs;

	dim_min_max(vertexs, X, &mins[0], &maxs[0]);
	dim_min_max(vertexs, Y, &mins[1], &maxs[1]);
	dim_min_max(vertexs, Z, &mins[2], &maxs[2]);

	normalize_dim(vertexs, X, mins[0], maxs[0]);
	normalize_dim(vertexs, Y, mins[1], maxs[1]);
	normalize_dim(vertexs, Z, mins[2], maxs[2]);
}
