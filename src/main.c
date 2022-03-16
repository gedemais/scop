#include "main.h"

static unsigned char	scop(t_env *env, int argc, char **argv)
{
	unsigned char	code;

	if ((code = setup(env, argc, argv)) != ERR_NONE)
		return (code);
	return (ERR_NONE);
}

int						main(int argc, char **argv)
{
	t_env			env;
	unsigned char	code;

	if ((code = scop(&env, argc, argv)) != ERR_NONE)
	{
		error_handler(&env, code);
		return (code);
	}
	return (ERR_NONE);
}
