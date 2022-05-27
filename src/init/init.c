#include "main.h"

static void		bind_actions_to_keys(t_env *env)
{
	// Function pointers array used to synthetize actions function
	static void	(*keys_fts[NB_KEYS])(t_env *env, int key) = {
													[KEY_EXIT] = exit_scop,
													[KEY_TOGGLE_ROTATION] = toggle_rotation,
													[KEY_TOGGLE_TEXTURE] = toggle_texture,
													[KEY_INCREASE_ROTATION_SPEED] = change_rotation_speed,
													[KEY_DECREASE_ROTATION_SPEED] = change_rotation_speed,
													[KEY_MOVE_OBJECT_FORWARD] = move_object,
													[KEY_MOVE_OBJECT_BACKWARD] = move_object,
													[KEY_MOVE_OBJECT_UP] = move_object,
													[KEY_MOVE_OBJECT_DOWN] = move_object,
													[KEY_MOVE_OBJECT_LEFT] = move_object,
													[KEY_MOVE_OBJECT_RIGHT] = move_object,
	};


	// Assignation of actions functions in respect with handled key indices.
	for (unsigned int i = 0; i < KEY_MAX; i++)
		env->keybinds_fts[env->settings.keys[i]] = keys_fts[i];
}

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

	if (argc != 2) // Arguments number check
		return (ERR_INVALID_ARGC);

	if ((code = load_obj_path(env, argv[1])) != ERR_NONE // Generates .obj file path
		|| (code = load_obj_file(env, argv[1])) != ERR_NONE // Loads obj data (vertices, faces, materials...)
		|| (code = load_settings(env)) != ERR_NONE // Loads settings data from Settings.toml
		|| (code = init_display(env)) != ERR_NONE // Inits display with glad and glfw3
		|| (code = init_shaders(env)) != ERR_NONE) // Load shader programs from .glsl files
		return (code);

	init_camera(env); // Initializes scene's camera
	bind_actions_to_keys(env); // Attribute action functions to keys loaded from settings file

	return (ERR_NONE);
}
