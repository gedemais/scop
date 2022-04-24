#include "main.h"

static unsigned char	load_shader_source(const char *path, const GLchar **ptr, size_t *file_size)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" : ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (ERR_OPENING_SHADER_FILE);
	}

	if (!(*ptr = read_file(fd, file_size)))
		return (ERR_READING_FILE);

	return (ERR_NONE);
}

static unsigned char	compile_shader(t_env *env, GLenum type, const GLchar *source, size_t size)
{
	char			info_log[4096];
	int				success;
	unsigned int	shader_id;

	shader_id = glCreateShader(type);

	if (type == GL_VERTEX_SHADER)
		env->vertex_shader_id = shader_id;
	else if (type == GL_FRAGMENT_SHADER)
		env->fragment_shader_id = shader_id;

	glShaderSource(shader_id, 1, &source, NULL);
	glCompileShader(shader_id);

	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) // If shader's compilation failed
	{
		bzero(info_log, sizeof(info_log));
		glGetShaderInfoLog(shader_id, sizeof(info_log), NULL, info_log);
		ft_putstr_fd(info_log, 2);
		munmap(source, size);
		return (ERR_FAILED_TO_COMPILE_SHADER);
	}
	munmap(source, size);

	return (ERR_NONE);
}

static unsigned char	build_shader(t_env *env, unsigned int id, const char *path)
{
	const GLchar	*shader_source;
	size_t			shader_size;
	GLenum			shader_type;
	unsigned char	code;

	if ((code = load_shader_source(path, &shader_source, &shader_size)))
		return (code);

	if (id == SHADER_VERTEX)
		shader_type = GL_VERTEX_SHADER;
	else if (id == SHADER_FRAGMENT)
		shader_type = GL_FRAGMENT_SHADER;
	else
		shader_type = 0;

	return (compile_shader(env, shader_type, shader_source, shader_size));
}

static unsigned char	link_shader_program(t_env *env)
{
	char	info_log[4096];
	int		success;

	env->shader_program = glCreateProgram();
	glAttachShader(env->shader_program, env->vertex_shader_id);
	glAttachShader(env->shader_program, env->fragment_shader_id);
	glLinkProgram(env->shader_program);

	glGetProgramiv(env->shader_program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(env->shader_program, 4096, NULL, info_log);
		ft_putendl_fd(info_log, 2);
		return (ERR_FAILED_TO_LINK_SHADER_PROGRAM);
	}


	return (ERR_NONE);
}

static unsigned char	init_buffers(t_env *env)
{
	GLsizeiptr		size;

	glGenBuffers(1, &env->vbo);
	glGenVertexArrays(1, &env->vao);

	glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
	glBindVertexArray(env->vao);

	size = (GLsizeiptr)sizeof(t_vec3d) * env->scene.vertexs.nb_cells;
	glBufferData(GL_ARRAY_BUFFER, size, env->scene.vertexs.c, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	if (!(env->scene.indices = malloc((unsigned long)env->scene.faces.nb_cells * sizeof(uint32_t) * 3)))
		return (ERR_MALLOC_FAILED);

	for (int i = 0; i < env->scene.faces.nb_cells * 3; i += 3)
	{
		memcpy(&env->scene.indices[i], dyacc(&env->scene.faces, i / 3), sizeof(uint32_t) * 3);
	}

	glGenBuffers(1, &env->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)env->scene.faces.nb_cells * (GLsizeiptr)sizeof(uint32_t) * 3, env->scene.indices, GL_STATIC_DRAW);

	return (ERR_NONE);
}

unsigned char			init_shaders(t_env *env)
{
	const char		*shaders_path[SHADER_MAX] = {"src/shaders/vertex.glsl",
												 "src/shaders/fragment.glsl"};
	unsigned char	code;

	for (unsigned int i = 0; i < SHADER_MAX; i++)
		if ((code = build_shader(env, i, shaders_path[i])))
			return (code);

	if ((code = link_shader_program(env)) != ERR_NONE
		|| (code = init_buffers(env)) != ERR_NONE)
		return (code);

	return (ERR_NONE);
}
