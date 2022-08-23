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

static void	mat4_pointat(mat4 m, t_vec3d from, t_vec3d to, t_vec3d world_up)
{
	t_vec3d		forward, up, right;

	forward = vec_sub(to, from);
    right = vec_cross(world_up, forward);
    up = vec_cross(forward, right);

	m[0] = right.x;
	m[1] = right.y;
	m[2] = right.z;
	m[3] = 0;
	m[4] = up.x;
	m[5] = up.y;
	m[6] = up.z;
	m[7] = 0;
	m[8] = forward.x;
	m[9] = forward.y;
	m[10] = forward.z;
	m[11] = 0;
	m[12] = -from.x;
	m[13] = -from.y;
	m[14] = -from.z;
	m[15] = 1;
}

bool	mat4_invert(mat4 m, mat4 invOut)
{
    mat4	inv;
	float	det;
    int		i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0.0f)
        return false;

    det = 1.0f / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}

void		mat4_view(t_cam *camera)
{
	mat4	rot;
	float	pitch, yaw, roll;

	camera->up = (t_vec3d){0, 1, 0, 0};
	camera->dir = (t_vec3d){0, 0, 1, 0};
	camera->target = (t_vec3d){0, 0, 1, 0};

	pitch = (float)ft_to_radians((double)camera->pitch);
	yaw = (float)ft_to_radians((double)camera->yaw);
	roll = (float)ft_to_radians((double)camera->roll);

	mat4_identity(camera->mats.view);
	mat4_translate(camera->mats.view, camera->pos.x, camera->pos.y, camera->pos.z);
	mat4_rotate(rot, pitch, yaw, roll);

	camera->dir = vec_normalize(mat4_mult_vec(rot, camera->target));
	camera->up = vec_normalize(mat4_mult_vec(rot, (t_vec3d){0, 1, 0, 0}));
	camera->target = vec_normalize(vec_add(camera->pos, camera->dir));
	mat4_pointat(camera->mats.view, camera->pos, camera->target, camera->up);
	mat4_invert(camera->mats.view, camera->mats.view);
}
