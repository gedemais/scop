#include "main.h"

static unsigned char	settings_readlines(char ***lines)
{
	char		*file;
	size_t		file_size;
	int			fd;

	// Open path to get fd and file size
	if ((fd = open("Settings.toml", O_RDONLY)) == -1)
	{
		perror(strerror(errno));
		return (ERR_OPENING_SETTINGS);
	}

	// Map file in memory
	if (!(file = read_file(fd, &file_size)))
		return (ERR_READING_SETTINGS);

	// Split file to lines
	if (!(*lines = ft_strsplit(file, "\n")))
	{
		munmap(file, file_size);
		return (ERR_MALLOC_FAILED);
	}

	// Free file mapping
	munmap(file, file_size);
	return (ERR_NONE);
}

static unsigned char	load_integer(char *line, char *token, long long int *n)
{
	*n = ft_atoi(token);
	if (*n < 1 || *n > SHRT_MAX)
	{
		ft_putendl_fd(line, 2);
		return (ERR_OUT_OF_BOUNDS_VALUE);
	}
	return (ERR_NONE);
}

static unsigned char	assign_value(t_env *env, unsigned int j, char *line, char *token)
{
	long long int	n = 0;
	unsigned char	code;

	// Read value associated to key (integer)

	if (j <= SET_TRANSITION_SPEED
		&& (code = load_integer(line, token, &n)) != ERR_NONE)
			return (code);
	//else if ((code = load_(line, token, &n)) != ERR_NONE)
	//	return (code);

	switch (j) {
		case SET_WIN_HEIGHT:
			env->settings.w_hgt = (uint16_t)n;
			break;
		case SET_WIN_WIDTH:
			env->settings.w_wdt = (uint16_t)n;
			break;
		case SET_ROTATION_SPEED:
			env->settings.rotation_speed = (uint16_t)n;
			break;
		case SET_TRANSITION_SPEED:
			env->settings.transition_speed = (uint16_t)n;
			break;
	};

	return (ERR_NONE);
}

static unsigned char	loader(t_env *env, char **lines)
{
	const char		*settings_keys[SET_MAX] = {
										"window_height",
										"window_width",
										"rotation_speed",
										"transition_speed"};
	bool			founds[SET_MAX];
	char			**tokens;
	unsigned char	code;
	bool			found;

	memset(founds, 0, sizeof(bool) * SET_MAX);
	for (unsigned int i = 0; lines[i]; i++)
	{
		if (!(tokens = ft_strsplit(lines[i], " \b\t\v\f\r")))
			return (ERR_MALLOC_FAILED);

		// First syntax check
		if (ft_tablen(tokens) != 3 || tokens[1][0] != '=' || tokens[1][1] != 0)
		{
			ft_putendl_fd(lines[i], 2);
			ft_free_ctab(tokens);
			return (ERR_INVALID_SYNTAX);
		}

		found = false;
		for (unsigned int j = 0; j < SET_MAX; j++)
			if (strcmp(tokens[0], settings_keys[j]) == 0)
			{
				if ((code = assign_value(env, j, lines[i], tokens[2])) != ERR_NONE)
				{
					ft_free_ctab(tokens);
					return (code);
				}
				found = true;
				founds[j] = true;
			}

		if (found == false)
		{
			ft_putendl_fd(lines[i], 2);
			ft_free_ctab(tokens);
			return (ERR_INVALID_SETTING_KEY);
		}
		ft_free_ctab(tokens);
	}

	for (unsigned int i = 0; i < SET_MAX; i++)
		if (founds[i] == false)
		{
			ft_putendl_fd(settings_keys[i], 2);
			return (ERR_SETTING_KEY_NOT_FOUND);
		}

	return (ERR_NONE);
}

unsigned char			load_settings(t_env *env)
{
	char			**lines;
	unsigned char	code;

	if ((code = settings_readlines(&lines)) != ERR_NONE)
		return (code);

	if ((code = loader(env, lines)) != ERR_NONE)
	{
		ft_free_ctab(lines);
		return (code);
	}

	ft_free_ctab(lines);

	printf("%d\n", env->settings.w_hgt);
	printf("%d\n", env->settings.w_wdt);
	printf("%d\n", env->settings.rotation_speed);
	printf("%d\n", env->settings.transition_speed);
	return (ERR_NONE);
}
