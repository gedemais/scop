#include "main.h"


unsigned char	setup(t_env *env, int argc, char **argv)
{
	unsigned char code;

	if (argc != 2)
		return (ERR_INVALID_ARGC);

	if ((code = load_obj_file(argv[1]))
		|| (code = load_mtl_file(argv[1]))
		|| (code = load_settings(env)) != ERR_NONE)
		return (code);

	return (ERR_NONE);
}
