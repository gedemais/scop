#include "main.h"

static unsigned char	load_obj_path(t_env *env, char *name)
{
	size_t len;

	if (!(env->obj_path = ft_strdup(name)))
		return (ERR_MALLOC_FAILED);

	len = ft_strlen(env->obj_path);
	if (len < 5 || ft_strcmp(&name[len - 4], ".obj"))
		return (ERR_INVALID_OBJ_FILE_EXTENSION);

	return (ERR_NONE);
}

unsigned char	init(t_env *env, int argc, char **argv)
{
	unsigned char code;

	if (argc != 2)
		return (ERR_INVALID_ARGC);

	if ((code = load_obj_path(env, argv[1])) != ERR_NONE
		|| (code = load_obj_file(env, argv[1])) != ERR_NONE
		|| (code = load_settings(env)) != ERR_NONE
		|| (code = init_display(env)) != ERR_NONE)
		return (code);

	return (ERR_NONE);
}
