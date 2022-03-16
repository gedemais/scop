#ifndef MAIN_H
# define MAIN_H

# include <OpenGL/gl.h>

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

# include "libft.h"

# include "error.h"

enum					e_default_settings_values
{
	DSV_W_XPOS = 200,
	DSV_W_YPOS = 200,
	DSV_W_WDT = 400,
	DSV_W_HGT = 400,
	DSV_ROTATION_SPEED = 10,
	DSV_TRANSITION_SPEED = 10
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
	float		rotation_speed;
	float		transition_speed;
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
	//t_events	events;
}				t_env;

unsigned char	setup(t_env *env, int argc, char **argv);

void	error_handler(t_env *env, unsigned char code);

void	free_env(t_env *env);

#endif
