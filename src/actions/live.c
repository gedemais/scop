#include "main.h"

void	move_object(t_env *env, int key)
{
	t_vec3d	translation = (t_vec3d){0, 0, 0, 0};

	if (key == gl_keys_values[env->settings.keys[KEY_MOVE_OBJECT_UP]])
		translation = vec_add(translation, (t_vec3d){0.0f, MOVE_SPEED, 0.0f, 0.0f});
	if (key == gl_keys_values[env->settings.keys[KEY_MOVE_OBJECT_DOWN]])
		translation = vec_add(translation, (t_vec3d){0.0f, -MOVE_SPEED, 0.0f, 0.0f});
	if (key == gl_keys_values[env->settings.keys[KEY_MOVE_OBJECT_LEFT]])
		translation = vec_add(translation, (t_vec3d){-MOVE_SPEED, 0.0f, 0.0f, 0.0f});
	if (key == gl_keys_values[env->settings.keys[KEY_MOVE_OBJECT_RIGHT]])
		translation = vec_add(translation, (t_vec3d){MOVE_SPEED, 0.0f, 0.0f, 0.0f});
	if (key == gl_keys_values[env->settings.keys[KEY_MOVE_OBJECT_FORWARD]])
		translation = vec_add(translation, (t_vec3d){0.0f, 0.0f, -MOVE_SPEED, 0.0f});
	if (key == gl_keys_values[env->settings.keys[KEY_MOVE_OBJECT_BACKWARD]])
		translation = vec_add(translation, (t_vec3d){0.0f, 0.0f, MOVE_SPEED, 0.0f});

	env->tst = vec_add(env->tst, translation);
}

void	move_camera(t_env *env, int key)
{
	t_cam	*cam;
	t_vec3d	up;
	t_vec3d	right;

	cam = &env->scene.cam;
	right = (t_vec3d){cam->dir.z, 0, -cam->dir.x, cam->dir.w};

	if (key == gl_keys_values[env->settings.keys[KEY_MOVE_CAM_RIGHT]])
		cam->pos = vec_add(cam->pos, vec_fmult(right, CAM_SPEED));
	if (key == gl_keys_values[env->settings.keys[KEY_MOVE_CAM_LEFT]])
		cam->pos = vec_add(cam->pos, vec_fmult(right, -CAM_SPEED));

	if (key == gl_keys_values[env->settings.keys[KEY_MOVE_CAM_FORWARD]])
		cam->pos = vec_add(cam->pos, vec_fmult(cam->dir, CAM_SPEED));
	if (key == gl_keys_values[env->settings.keys[KEY_MOVE_CAM_BACKWARD]])
		cam->pos = vec_add(cam->pos, vec_fmult(cam->dir, -CAM_SPEED));
}
