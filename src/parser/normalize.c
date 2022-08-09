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
		// Normalize
		comp[dim] = (((comp[dim] - min) * (VERTEX_NORMALIZE_RANGE - -VERTEX_NORMALIZE_RANGE)) / (max - min)) + -VERTEX_NORMALIZE_RANGE;
	}
}

void				normalize_vertexs(t_env *env)
{
	t_dynarray	*vertexs;
	float		mins[3];
	float		maxs[3];
	float		min;
	float		max;

	vertexs = &env->scene.vertexs;

	// Find min and max for three dimensions
	dim_min_max(vertexs, X, &mins[0], &maxs[0]);
	dim_min_max(vertexs, Y, &mins[1], &maxs[1]);
	dim_min_max(vertexs, Z, &mins[2], &maxs[2]);

	min = mins[0] < mins[1] ? mins[0] : mins[1];
	min = min < mins[2] ? min : mins[2];

	max = maxs[0] > maxs[1] ? maxs[0] : maxs[1];
	max = max > maxs[2] ? max : maxs[2];

	//printf("%f %f %f -> %f\n", (double)mins[0], (double)mins[1], (double)mins[2], (double)min);
	//printf("%f %f %f -> %f\n", (double)maxs[0], (double)maxs[1], (double)maxs[2], (double)max);

	// Normalize three dimensions
	normalize_dim(vertexs, X, min, max);
	normalize_dim(vertexs, Y, min, max);
	normalize_dim(vertexs, Z, min, max);
}
