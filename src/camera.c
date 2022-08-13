#include "main.h"

//static void	init_matrices(t_cam *cam)
//{
//	/* set the model to face positive Z and stand back */
//	mat4_rotate(cam->mats.model, 0.0f, (float)M_PI, 0.0f);
//	mat4_translate(cam->mats.model, 0, 0, -5);
//	/* set the view with camera orientations and rotations */
//	mat4_view(cam);
//	/* set the projection with camera data */
//	mat4_projection(cam->mats.projection, cam->fovd, cam->fnear, cam->ffar, cam->aspect_ratio);
//}

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

//	init_matrices(cam);
}
