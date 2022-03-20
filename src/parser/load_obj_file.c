#include "main.h"

unsigned char	load_obj_file(char *path)
{
	char			**lines;
	unsigned char	code;

	if ((code = readlines(path, &lines)) != ERR_NONE)
		return (code);

	for (unsigned int i = 0; lines[i]; i++)
		printf("%s\n", lines[i]);
	printf("-----------------------\n");

	return (ERR_NONE);
}
