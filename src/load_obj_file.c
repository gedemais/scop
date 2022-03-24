#include "main.h"

static const char		*obj_lines_ids[OBJ_MAX] = {	[OBJ_COMMENT] = "#",
											[OBJ_MTLLIB] = "mtllib",
											[OBJ_OBJECT_NAME] = "o",
											[OBJ_VERTEX] = "v",
											[OBJ_USEMTL] = "usemtl",
											[OBJ_FACE] = "f",
											[OBJ_SMOOTH_SHADING] = "s"};

static int16_t	used_mtl = SHRT_MAX;
static int32_t	current_mesh = INT_MAX;

////////////////////////////// Loading Functions //////////////////////////////

static unsigned char	obj_mtllib_loader(t_env *env, char **tokens)
{
	(void)env;
	(void)tokens;
	printf("%s\n", __FUNCTION__);
	return (ERR_NONE);
}

static unsigned char	obj_object_name_loader(t_env *env, char **tokens)
{
	t_dynarray	*meshs;
	t_mesh		new;

	if (ft_tablen(tokens) != 2)
		return (ERR_INVALID_OBJECT_NAME);

	new.o = (t_vec3d){0.0, 0.0, 0.0, 0.0};
	if (!(new.name = ft_strdup(tokens[1]))
		|| init_dynarray(&new.faces, sizeof(uint32_t), 256))
		return (ERR_MALLOC_FAILED);

	meshs = &env->scene.meshs;
	if ((meshs->c == NULL && init_dynarray(meshs, sizeof(t_mesh), 1))
		|| push_dynarray(meshs, &new, false))
		return (ERR_MALLOC_FAILED);

	current_mesh = 0;

	return (ERR_NONE);
}

static unsigned char	obj_vertex_loader(t_env *env, char **tokens)
{
	t_vec3d	new;

	if (ft_tablen(tokens) != 4)
		return (ERR_INVALID_VERTEX_FORMAT);

	if (env->scene.vertexs.c == NULL
		&& init_dynarray(&env->scene.vertexs, sizeof(t_vec3d), 256))
		return (ERR_MALLOC_FAILED);

	new.x = (float)atof(tokens[1]);
	new.y = (float)atof(tokens[2]);
	new.z = (float)atof(tokens[3]);
	new.w = 0.0;

	if (push_dynarray(&env->scene.vertexs, &new, false))
		return (ERR_MALLOC_FAILED);

	ft_free_ctab(tokens);
	return (ERR_NONE);
}

static unsigned char	obj_usemtl_loader(t_env *env, char **tokens)
{
	(void)env;
	(void)tokens;
	printf("%s\n", __FUNCTION__);
	return (ERR_NONE);
}

static unsigned char	check_face_indexes(t_env *env, t_face new)
{
	if (new.a < 0 || new.a >= env->scene.vertexs.nb_cells
		|| new.b < 0 || new.b >= env->scene.vertexs.nb_cells
		|| new.c < 0 || new.c >= env->scene.vertexs.nb_cells)
		return (ERR_INVALID_VERTEX_INDEX_FOR_FACE);
	return (ERR_NONE);
}

static unsigned char	triangulation(t_env *env, t_mesh *parent, uint32_t a_index, char **tokens, unsigned short nb_vertexs)
{
	t_face	news[2];

	if (nb_vertexs == 4) // Quad -> 2 triangles
	{
		uint32_t	b_index = a_index + 1;
		news[0].a = (int32_t)ft_atoi(tokens[1]) - 1;
		news[0].b = (int32_t)ft_atoi(tokens[2]) - 1;
		news[0].c = (int32_t)ft_atoi(tokens[3]) - 1;

		news[1].a = (int32_t)ft_atoi(tokens[1]) - 1;
		news[1].b = (int32_t)ft_atoi(tokens[3]) - 1;
		news[1].c = (int32_t)ft_atoi(tokens[4]) - 1;

		if (push_dynarray(&env->scene.faces, &news[0], false)
			|| push_dynarray(&env->scene.faces, &news[1], false))
			return (ERR_MALLOC_FAILED);

		if (push_dynarray(&parent->faces, &a_index, false)
			|| push_dynarray(&parent->faces, &b_index, false))
			return (ERR_MALLOC_FAILED);

		if (check_face_indexes(env, news[0]) != ERR_NONE
			|| check_face_indexes(env, news[1]) != ERR_NONE)
			return (ERR_INVALID_VERTEX_INDEX_FOR_FACE);
	}
	return (ERR_NONE);
}

static unsigned char	obj_face_loader(t_env *env, char **tokens)
{
	t_face			new;
	t_mesh			*parent;
	unsigned short	nb_vertexs;
	uint32_t		face_index;

	parent = dyacc(&env->scene.meshs, (int)current_mesh);
	nb_vertexs = (unsigned short)ft_tablen(tokens) - 1;

	if (env->scene.faces.c == NULL
		&& init_dynarray(&env->scene.faces, sizeof(t_face), 256))
		return (ERR_MALLOC_FAILED);

	face_index = (uint32_t)env->scene.faces.nb_cells;

	if (nb_vertexs == 3)
	{
		new.a = (int32_t)ft_atoi(tokens[1]) - 1;
		new.b = (int32_t)ft_atoi(tokens[2]) - 1;
		new.c = (int32_t)ft_atoi(tokens[3]) - 1;
		new.mtl = used_mtl;

		if (push_dynarray(&env->scene.faces, &new, false)
			|| push_dynarray(&parent->faces, &face_index, false))
			return (ERR_MALLOC_FAILED);

		return (check_face_indexes(env, new));
	}
	else if (nb_vertexs < 5)
		return (triangulation(env, parent, face_index, tokens, nb_vertexs));

	return (ERR_INVALID_PRIMITIVE_DESCRIPTION);
}

///////////////////////////////////////////////////////////////////////////////

static unsigned char	obj_loader(t_env *env, char *line)
{
	static unsigned char	(*obj_loading_fts[OBJ_MAX])(t_env *, char **) = {
											[OBJ_COMMENT] = NULL,
											[OBJ_MTLLIB] = obj_mtllib_loader,
											[OBJ_OBJECT_NAME] = obj_object_name_loader,
											[OBJ_VERTEX] = obj_vertex_loader,
											[OBJ_USEMTL] = obj_usemtl_loader,
											[OBJ_FACE] = obj_face_loader,
											[OBJ_SMOOTH_SHADING] = NULL};
	char				**tokens;

	if (!(tokens = ft_strsplit(line, "\b\t\v\f\r ")))
		return (ERR_MALLOC_FAILED);

	for (unsigned int i = 0; i < OBJ_MAX; i++)
		if (ft_strcmp(tokens[0], obj_lines_ids[i]) == 0)
		{
			if ((i == OBJ_VERTEX || i == OBJ_FACE) && current_mesh == INT_MAX)
				return (ERR_NO_DEFINED_OBJECT);
			return (obj_loading_fts[i] ? obj_loading_fts[i](env, tokens) : ERR_NONE);
		}

	ft_free_ctab(tokens);
	return (ERR_INVALID_OBJ_LINE_ID);
}

unsigned char			load_obj_file(t_env *env, char *path)
{
	char			**lines;
	unsigned char	code;

	if ((code = readlines(path, &lines)) != ERR_NONE)
		return (code);

	for (unsigned int i = 0; lines[i]; i++)
		if ((code = obj_loader(env, lines[i])))
			return (code);

	return (ERR_NONE);
}
