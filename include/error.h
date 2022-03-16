#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>

enum	e_error_id
{
	ERR_NONE,
	ERR_INVALID_ARGC,
	ERR_MAX
};

typedef	struct	s_error
{
	char	msg[64];
	bool	usage;
}				t_error;

static const t_error	errors[ERR_MAX] = {
		[ERR_INVALID_ARGC] = {"Invalid number of arguments.", true}
};

#endif
