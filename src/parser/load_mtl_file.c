#include "main.h"

static char	*make_mtl_path(char *path)
{
	char	*mtl_path;
	size_t	length;

	if (!(mtl_path = ft_strdup(path)))
		return (NULL);

	length = ft_strlen(mtl_path);
	ft_strncpy(&mtl_path[length - 3], "mtl", 3);
	printf("%s\n", mtl_path);
	return (mtl_path);
}

unsigned char	load_mtl_file(char *path)
{
	char			**lines;
	char			*mtl_path;
	unsigned char	code;

	if (!(mtl_path = make_mtl_path(path)))
		return (ERR_MALLOC_FAILED);

	if ((code = readlines(mtl_path, &lines)) != ERR_NONE)
	{
		free(mtl_path);
		return (code);
	}
	free(mtl_path);

	for (unsigned int i = 0; lines[i]; i++)
		printf("%s\n", lines[i]);
	printf("-----------------------\n");

	return (ERR_NONE);
}
