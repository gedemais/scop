#ifndef ERROR_H
#define ERROR_H

#include <stdbool.h>

enum e_error_id
{
	ERR_NONE,
	ERR_INVALID_ARGC,
	ERR_FAILED_WIN,
	ERR_FAILED_GLAD,
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
	[ERR_FAILED_GLAD] = {"Failed to initialize GLAD", true}}

#endif
