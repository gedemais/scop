#ifndef LIB_VEC_H
# define LIB_VEC_H

# include <math.h>
# include <stdbool.h>

typedef struct	s_vec3d
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec3d;

t_vec3d		vec_fdiv(t_vec3d a, float n);
t_vec3d		vec_fmult(t_vec3d a, float n);
t_vec3d		vec_fsub(t_vec3d a, float n);

t_vec3d		vec_cross(t_vec3d a, t_vec3d b);

t_vec3d		zero_vector(void);

t_vec3d		vec_add(t_vec3d a, t_vec3d b);
t_vec3d		vec_sub(t_vec3d a, t_vec3d b);
t_vec3d		vec_mult(t_vec3d a, t_vec3d b);
t_vec3d		vec_div(t_vec3d a, t_vec3d b);
t_vec3d		vec_relu(t_vec3d v);

#endif
