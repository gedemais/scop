#include "main.h"

void	exit_scop(t_env *env, int key)
{
	(void)key;
	free_env(env);
	exit(EXIT_SUCCESS);
}

void	toggle_rotation(t_env *env, int key)
{
	(void)key;
	env->settings.rotation = !env->settings.rotation;
}

void	toggle_texture(t_env *env, int key)
{
	(void)key;
	env->settings.textured = !env->settings.textured;
}

void	change_rotation_speed(t_env *env, int key)
{
	(void)key;
	env->settings.rotation_speed += ROTATION_SPEED_DELTA;
}
