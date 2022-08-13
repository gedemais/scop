#include "main.h"


void		mat4_projection(mat4 m, float fov, float near, float far, float ratio)
{
	float	e;

	mat4_identity(m);
	e = 1 / (tanf(fov / 2.0f));
	m[0] = e / ratio;
	m[5] = e;
	m[10] = (near + far) / (near - far);
	m[11] = (2 * near * far) / (near - far);
	m[14] = -1;
}

static void	mat4_pointat(mat4 m, t_vec3d from, t_vec3d to, t_vec3d up)
{
	t_vec3d		forward, new_up, right;

	forward = vec_normalize(vec_sub(to, from));
	new_up = vec_fmult(forward, vec_dot(up, forward));
	new_up = vec_sub(up, new_up);
	right = vec_cross(new_up, forward);

	m[0] = right.x;
	m[1] = right.y;
	m[2] = right.z;
	m[3] = 0;
	m[3] = -vec_dot(right, from);
	m[4] = new_up.x;
	m[5] = new_up.y;
	m[6] = new_up.z;
	m[7] = 0;
	m[7] = -vec_dot(new_up, from);
	m[8] = forward.x;
	m[9] = forward.y;
	m[10] = forward.z;
	m[11] = 0;
	m[11] = -vec_dot(forward, from);
	m[12] = from.x;
	m[13] = from.y;
	m[14] = from.z;
	m[15] = 1;
}

void		mat4_view(t_cam *camera)
{
	mat4	rot;
	t_vec3d	target;
	float	pitch, yaw, roll;

	pitch = (float)ft_to_radians((double)camera->pitch);
	yaw = (float)ft_to_radians((double)camera->yaw);
	roll = (float)ft_to_radians((double)camera->roll);
	mat4_rotate(rot, pitch, yaw, roll);

	camera->dir = mat4_mult_vec(rot, camera->dir);
	camera->up = mat4_mult_vec(rot, camera->up);
	target = vec_add(camera->pos, camera->dir);
	mat4_pointat(camera->mats.view, camera->pos, target, camera->up);
}
