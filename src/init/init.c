#include "main.h"


unsigned char	init(t_env *env, int argc, char **argv)
{
	unsigned char code;

	if (argc != 2)
		return (ERR_INVALID_ARGC);

	if ((code = load_obj_file(env, argv[1])) != ERR_NONE
		|| (code = load_settings(env)) != ERR_NONE)
		return (code);

	return (ERR_NONE);
}
