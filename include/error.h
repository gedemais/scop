#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>

enum	e_error_id
{
	ERR_NONE,
	ERR_INVALID_ARGC,
	ERR_OPENING_FILE,
	ERR_READING_FILE,
	ERR_MALLOC_FAILED,
	ERR_INVALID_SYNTAX,
	ERR_OUT_OF_BOUNDS_VALUE,
	ERR_INVALID_SETTING_KEY,
	ERR_SETTING_KEY_NOT_FOUND,
	ERR_INVALID_OBJ_LINE_ID,
	ERR_MAX
};

typedef	struct	s_error
{
	char	msg[64];
	bool	usage;
}				t_error;

static const t_error	errors[ERR_MAX] = {
		[ERR_INVALID_ARGC] = {"Invalid number of arguments.", true},
		[ERR_OPENING_FILE] = {"Can not open file.", false},
		[ERR_READING_FILE] = {"Can not read file.", false},
		[ERR_MALLOC_FAILED] = {"malloc() call failed.", false},
		[ERR_INVALID_SYNTAX] = {"Invalid syntax in Settings.toml.", false},
		[ERR_OUT_OF_BOUNDS_VALUE] = {"Out of bounds value in Settings.toml.", false},
		[ERR_INVALID_SETTING_KEY] = {"Unrecognized setting key.", false},
		[ERR_SETTING_KEY_NOT_FOUND] = {"Missing setting.", false},
		[ERR_INVALID_OBJ_LINE_ID] = {"Invalid line identifier in .obj file.", false}
};

#endif
