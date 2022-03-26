#include "main.h"

unsigned char setup(t_env *env, int argc, char **argv)
{
	(void)argc;
	(void)argv;

	env->settings.w_wdt = 800;
	env->settings.w_hgt = 600;

	return (ERR_NONE);
}

static unsigned char scop(t_env *env, int argc, char **argv)
{
	unsigned char code;

	if ((code = setup(env, argc, argv)) != ERR_NONE)
		return (code);
	if ((code = init_display(env)) != ERR_NONE)
		return (code);
	if ((code = display_loop(env)) != ERR_NONE)
		return (code);
	return (code);
}

int main(int argc, char **argv)
{
	t_env env;
	unsigned char code;

	memset(&env, 0, sizeof(t_env));
	if ((code = scop(&env, argc, argv)) != ERR_NONE)
	{
		error_handler(&env, code);
		return (code);
	}
	return (ERR_NONE);
}
