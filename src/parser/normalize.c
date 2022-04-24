#include "main.h"

// Axis enumeration, simple abstraction for memory copies
enum	e_axis
{
	X,
	Y,
	Z
};

// Find min and max values in a specific dimension of every vertices
static void	dim_min_max(t_dynarray *vertexs, size_t dim, float *min, float *max)
{
	float	*comp;

	*min = FLT_MAX; // Set min to max float value and viceversa
	*max = FLT_MIN;
	for (int i = 0; i < vertexs->nb_cells; i++)
	{
		comp = (float*)dyacc(vertexs, i); // Access the vector, using dim to get the right component

		if (comp[dim] < *min)
			*min = comp[dim];
		else if (comp[dim] > *max)
			*max = comp[dim];
	}
}

static void			normalize_dim(t_dynarray *vertexs, size_t dim, float min, float max)
{
	float	*comp;

	// Iterate through vertexs to normalize a specific dimension of the vertexs pool
	for (int i = 0; i < vertexs->nb_cells; i++)
	{
		comp = (float*)dyacc(vertexs, i);
		// Normalize to -1.0 <=> 1.0
		comp[dim] = (((comp[dim] - min) * (1.0f - -1.0f)) / (max - min)) + -1.0f;
	}
}

void				normalize_vertexs(t_env *env)
{
	t_dynarray	*vertexs;
	float		mins[3];
	float		maxs[3];

	vertexs = &env->scene.vertexs;

	// Find min and max for three dimensions
	dim_min_max(vertexs, X, &mins[0], &maxs[0]);
	dim_min_max(vertexs, Y, &mins[1], &maxs[1]);
	dim_min_max(vertexs, Z, &mins[2], &maxs[2]);

	// Normalize three dimensions
	normalize_dim(vertexs, X, mins[0], maxs[0]);
	normalize_dim(vertexs, Y, mins[1], maxs[1]);
	normalize_dim(vertexs, Z, mins[2], maxs[2]);
}
