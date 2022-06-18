#include "main.h"

static void	init_projection_matrix(t_cam *cam)
{
	cam->mats.p_m[0][0] = cam->aspect_ratio * cam->fovr;
	cam->mats.p_m[1][1] = cam->fovr;
	cam->mats.p_m[2][2] = cam->ffar / cam->fdelta;
	cam->mats.p_m[3][2] = (-cam->ffar * cam->fnear) / cam->fdelta;
	cam->mats.p_m[2][3] = 1.0f;
	cam->mats.p_m[3][3] = 0.0f;
}

static void	init_matrices(t_cam *cam)
{
	unsigned int	i;

	i = 0;
	while (i < 4)
	{
		ft_memset(&cam->mats.w_m[i][0], 0, sizeof(float) * 4);
		ft_memset(&cam->mats.v_m[i][0], 0, sizeof(float) * 4);
		ft_memset(&cam->mats.p_m[i][0], 0, sizeof(float) * 4);
		ft_memset(&cam->mats.rx_m[i][0], 0, sizeof(float) * 4);
		ft_memset(&cam->mats.ry_m[i][0], 0, sizeof(float) * 4);
		ft_memset(&cam->mats.rz_m[i][0], 0, sizeof(float) * 4);
		ft_memset(&cam->mats.crx_m[i][0], 0, sizeof(float) * 4);
		ft_memset(&cam->mats.cry_m[i][0], 0, sizeof(float) * 4);

		cam->mats.w_m[i][i] = 1.0f;
		cam->mats.v_m[i][i] = 1.0f;
		cam->mats.p_m[i][i] = 1.0f;
		cam->mats.rx_m[i][i] = 1.0f;
		cam->mats.ry_m[i][i] = 1.0f;
		cam->mats.rz_m[i][i] = 1.0f;
		cam->mats.crx_m[i][i] = 1.0f;
		cam->mats.cry_m[i][i] = 1.0f;
		i++;
	}

	init_projection_matrix(cam);
}

void		init_camera(t_env *env)
{
	t_cam	*cam;

	cam = (t_cam*)&env->scene.cam;
	cam->aspect_ratio = (float)env->settings.w_hgt / (float)env->settings.w_wdt;

	// Far and near plane definitions
	cam->fnear = 0.01f;
	cam->ffar = 100000.0f;
	cam->fdelta = cam->ffar - cam->fnear;

	// FOV
	cam->fovd = 90.0f;
	cam->fovr = 1.0f / tanf(cam->fovd * 0.5f / 180.0f * 3.14159f);

	// Camera's starting position and orientation
	cam->pos = (t_vec3d){0.0f, 0.0f, 0.0f, 0.0f};
	cam->up = (t_vec3d){0.0f, 1.0f, 0.0f, 0.0f};
	cam->dir = (t_vec3d){0.0f, 0.0f, 1.0f, 0.0f};

	// Camera rotations
	cam->roll = 0;
	cam->pitch = 0;
	cam->yaw = 0;

	init_matrices(cam);
}
