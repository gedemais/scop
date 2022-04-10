#include "main.h"

void	rotate_mesh(t_env *env)
{
	(void)env;
}

void	transate_mesh(t_env *env)
{
	(void)env;
}

// Moves directions :

void	move_object(t_env *env, int key)
{
	t_vec3d	tst = (t_vec3d){0.0f, 0.0f, 0.0f, 0.0f};

	if (key == env->settings.keys[KEY_MOVE_OBJECT_UP])
		tst = vec_add(tst, (t_vec3d){0.0f, 1.0f, 0.0f, 0.0f});
	if (key == env->settings.keys[KEY_MOVE_OBJECT_DOWN])
		tst = vec_add(tst, (t_vec3d){0.0f, -1.0f, 0.0f, 0.0f});
	if (key == env->settings.keys[KEY_MOVE_OBJECT_LEFT])
		tst = vec_add(tst, (t_vec3d){-1.0f, 0.0f, 0.0f, 0.0f});
	if (key == env->settings.keys[KEY_MOVE_OBJECT_RIGHT])
		tst = vec_add(tst, (t_vec3d){1.0f, 0.0f, 0.0f, 0.0f});
	if (key == env->settings.keys[KEY_MOVE_OBJECT_FORWARD])
		tst = vec_add(tst, (t_vec3d){0.0f, 0.0f, -1.0f, 0.0f});
	if (key == env->settings.keys[KEY_MOVE_OBJECT_BACKWARD])
		tst = vec_add(tst, (t_vec3d){0.0f, 0.0f, 1.0f, 0.0f});

	printf("%f %f %f %f\n", (double)tst.x, (double)tst.y, (double)tst.z, (double)tst.w);
}
