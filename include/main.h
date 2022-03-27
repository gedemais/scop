#ifndef MAIN_H
# define MAIN_H

# include "glad.h"
# include <GLFW/glfw3.h>

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

# include "libft.h"
# include "lib_vec.h"
# include "bmp.h"

# include "error.h"
# include "parser.h"
# include "scene.h"
# include "keys.h"

enum					e_settings
{
	SET_WIN_HEIGHT,
	SET_WIN_WIDTH,
	SET_ROTATION_SPEED,
	SET_TRANSITION_SPEED,
	SET_KEY_EXIT,
	SET_KEY_TOGGLE_ROTATION,
	SET_KEY_TOGGLE_TEXTURE,
	SET_KEY_INCREASE_ROTATION_SPEED,
	SET_KEY_DECREASE_ROTATION_SPEED,
	SET_KEY_MOVE_OBJECT_FORWARD,
	SET_KEY_MOVE_OBJECT_BACKWARD,
	SET_KEY_MOVE_OBJECT_UP,
	SET_KEY_MOVE_OBJECT_DOWN,
	SET_KEY_MOVE_OBJECT_LEFT,
	SET_KEY_MOVE_OBJECT_RIGHT,
	SET_MAX
};

enum					e_keys
{
	KEY_EXIT,
	KEY_TOGGLE_ROTATION,
	KEY_TOGGLE_TEXTURE,
	KEY_INCREASE_ROTATION_SPEED,
	KEY_DECREASE_ROTATION_SPEED,
	KEY_MOVE_OBJECT_FORWARD,
	KEY_MOVE_OBJECT_BACKWARD,
	KEY_MOVE_OBJECT_UP,
	KEY_MOVE_OBJECT_DOWN,
	KEY_MOVE_OBJECT_LEFT,
	KEY_MOVE_OBJECT_RIGHT,
	KEY_MAX
};

typedef struct	s_settings
{
	uint16_t	w_wdt;
	uint16_t	w_hgt;
	uint16_t	rotation_speed;
	uint16_t	transition_speed;
	uint8_t		keys[KEY_MAX];
	char		pad;
}				t_settings;

/*typedef struct	s_event
{
	bool		keys[NB_KEYS];
	bool		buttons[BUTTON_MAX]; // Later
	uint16_t	mouse_x; // Later
	uint16_t	mouse_y; // Later
}				t_event;*/

typedef struct	s_env
{
	t_settings	settings;
	char		pad[4];
	t_scene		scene;
	char		*obj_path;
	GLFWwindow	*window;
	//t_events	events;
}				t_env;

unsigned char	init(t_env *env, int argc, char **argv);

// OpenGL
unsigned char   init_display(t_env *env);
unsigned char   display_loop(t_env *env);
//

// Parsing
unsigned char	readlines(char *path, char ***lines);
unsigned char	load_obj_file(t_env *env, char *path);
unsigned char	load_settings(t_env *env);
unsigned char	obj_mtllib_loader(t_env *env, char **tokens);

unsigned char	obj_face_loader(t_env *env, char **tokens);
unsigned char	create_default_mesh(t_env *env);

unsigned char	mtl_newmtl_loader(t_env *env, char **tokens);
unsigned char	mtl_diffuse_color_loader(t_env *env, char **tokens);
unsigned char	mtl_alpha_component_loader(t_env *env, char **tokens);
unsigned char	mtl_texture_image_loader(t_env *env, char **tokens);

// Ending
void			error_handler(t_env *env, unsigned char code);
void			free_env(t_env *env);

// Function pointers array linking actions functions with key binds
static unsigned char	(*keys_fts[KEY_MAX])(t_env *env);

static const char		*settings_keys[SET_MAX] = {
										"window_height",
										"window_width",
										"rotation_speed",
										"transition_speed",
										"exit",
										"toggle_rotation",
										"toggle_texture",
										"increase_rotation_speed",
										"decrease_rotation_speed",
										"move_object_forward",
										"move_object_backward",
										"move_object_up",
										"move_object_down",
										"move_object_left",
										"move_object_right"
										};

#endif
