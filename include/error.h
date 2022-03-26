#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>

enum e_error_id
{
	ERR_NONE,
	ERR_INVALID_ARGC,
	ERR_FAILED_WIN,
	ERR_FAILED_GLAD,
	ERR_OPENING_SETTINGS,
	ERR_READING_SETTINGS,
	ERR_MALLOC_FAILED,
	ERR_INVALID_SYNTAX,
	ERR_OUT_OF_BOUNDS_VALUE,
	ERR_INVALID_SETTING_KEY,
	ERR_SETTING_KEY_NOT_FOUND,
	ERR_MAX
};

typedef struct s_error
{
	char msg[64];
	bool usage;
} t_error;

static const t_error errors[ERR_MAX] = {
	[ERR_INVALID_ARGC] = {"Invalid number of arguments.", true},
	[ERR_FAILED_WIN] = {"Failed to create GLFW window", true},
	[ERR_FAILED_GLAD] = {"Failed to initialize GLAD", true},
	[ERR_OPENING_SETTINGS] = {"Can not open Settings.toml.", false},
	[ERR_READING_SETTINGS] = {"Settings.toml reading failed.", false},
	[ERR_MALLOC_FAILED] = {"malloc() call failed.", false},
	[ERR_INVALID_SYNTAX] = {"Invalid syntax in Settings.toml", false},
	[ERR_OUT_OF_BOUNDS_VALUE] = {"Out of bounds value in Settings.toml", false},
	[ERR_INVALID_SETTING_KEY] = {"Unrecognized setting key.", false},
	[ERR_SETTING_KEY_NOT_FOUND] = {"Missing setting.", false}};

#endif
