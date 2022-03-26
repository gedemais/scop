#ifndef MAIN_H
# define MAIN_H

# include <OpenGL/gl.h>

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

enum					e_default_settings_values
{
	DSV_W_XPOS = 200,
	DSV_W_YPOS = 200,
	DSV_W_WDT = 400,
	DSV_W_HGT = 400,
	DSV_ROTATION_SPEED = 10,
	DSV_TRANSITION_SPEED = 10
};

enum					e_settings
{
	SET_WIN_HEIGHT,
	SET_WIN_WIDTH,
	SET_ROTATION_SPEED,
	SET_TRANSITION_SPEED,
	SET_MAX
};

enum					e_keys
{
	KEY_EXIT,
	KEY_ROTATION,
	KEY_TRANSITION,
	KEY_ROTATION_SPEED_UP,
	KEY_ROTATION_SPEED_DOWN,
	KEY_MOVE_X_FORWARD,
	KEY_MOVE_X_BACKWARD,
	KEY_MOVE_Y_FORWARD,
	KEY_MOVE_Y_BACKWARD,
	KEY_MOVE_Z_FORWARD,
	KEY_MOVE_Z_BACKWARD,
	KEY_MAX
};

typedef struct	s_settings
{
	uint16_t	w_wdt;
	uint16_t	w_hgt;
	uint16_t	rotation_speed;
	uint16_t	transition_speed;
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
	t_scene		scene;
	char		*obj_path;
	//t_events	events;
}				t_env;

unsigned char	readlines(char *path, char ***lines);
unsigned char	load_obj_file(t_env *env, char *path);

unsigned char	obj_face_loader(t_env *env, char **tokens);
unsigned char	create_default_mesh(t_env *env);
unsigned char	obj_mtllib_loader(t_env *env, char **tokens);


unsigned char	mtl_newmtl_loader(t_env *env, char **tokens);
unsigned char	mtl_diffuse_color_loader(t_env *env, char **tokens);
unsigned char	mtl_alpha_component_loader(t_env *env, char **tokens);
unsigned char	mtl_texture_image_loader(t_env *env, char **tokens);

unsigned char	init(t_env *env, int argc, char **argv);
unsigned char	load_settings(t_env *env);


void			error_handler(t_env *env, unsigned char code);

void			free_env(t_env *env);

#endif
