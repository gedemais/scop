#include "main.h"

unsigned char	setup(t_env *env, int argc, char **argv)
{
	(void)env;
	(void)argv;
	if (argc != 2)
		return (ERR_INVALID_ARGC);
	return (ERR_NONE);
}
