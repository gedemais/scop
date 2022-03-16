#include "main.h"

char	*read_file(int fd, size_t *file_size)
{
	struct stat	s;
	char		*file;

	fstat(fd, &s);
	*file_size = (size_t)s.st_size;
	file = mmap(NULL, (size_t)s.st_size, PROT_READ, MAP_SHARED, fd, 0);

	if (file == MAP_FAILED)
		return (NULL);

	return (file);
}
