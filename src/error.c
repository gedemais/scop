#include "main.h"

void	error_handler(t_env *env, unsigned char code)
{
	const char	*usage = "./scop [.obj file path]\n";
	const char	*msg;

	if (code >= ERR_MAX)
		return ;

	msg = &errors[code].msg[0];

	write(2, "./scop : ", 9);
	write(2, "error : ", 8);
	write(2, msg, strlen(msg));
	write(2, "\n", 1);

	if (errors[code].usage)
		write(2, usage, strlen(usage));

	free_env(env);
}
