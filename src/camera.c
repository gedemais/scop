#include "main.h"

void		init_camera(t_env *env)
{
	t_cam	*cam;

	cam = (t_cam*)&env->scene.cam;
	cam->aspect_ratio = (float)env->settings.w_wdt / (float)env->settings.w_hgt;

	// Far and near plane definitions
	cam->fnear = 0.01f;
	cam->ffar = 100000.0f;
	cam->fdelta = cam->ffar - cam->fnear;

	// FOV
	cam->fovd = 70.0f;
	cam->fovr = 1.0f / tanf(cam->fovd * 0.5f / 180.0f * 3.14159f);

	// Camera's starting position and orientation
	cam->pos = (t_vec3d){0.0f, 0.0f, 0.0f, 0.0f};
	cam->up = (t_vec3d){0.0f, 1.0f, 0.0f, 0.0f};
	cam->dir = (t_vec3d){0.0f, 0.0f, 1.0f, 0.0f};

	// Camera rotations
	cam->roll = 0;
	cam->pitch = 0;
	cam->yaw = 0;

	env->tst = (t_vec3d){0, 0, -0.8f, 0}; // Initialize object position further
	env->rot = (t_vec3d){0, ft_to_radians(-90.0f), 0, 0}; // Initialize object angle
}
