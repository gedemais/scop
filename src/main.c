#include "main.h"

int	main(int argc, char **argv)
{
	t_env			env;
	unsigned char	code;

	if ((code = setup(&env, argc, argv)) != ERR_NONE)
		return (code);
	return (0);
}
