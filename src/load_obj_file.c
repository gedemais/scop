#include "main.h"

////////////////////////////// Loading Functions //////////////////////////////

static unsigned char	obj_mtllib_loader(t_env *env, char **tokens)
{
	(void)env;
	(void)tokens;
	return (ERR_NONE);
}

static unsigned char	obj_object_name_loader(t_env *env, char **tokens)
{
	(void)env;
	(void)tokens;
	return (ERR_NONE);
}

static unsigned char	obj_vertex_loader(t_env *env, char **tokens)
{
	(void)env;
	(void)tokens;
	return (ERR_NONE);
}

static unsigned char	obj_usemtl_loader(t_env *env, char **tokens)
{
	(void)env;
	(void)tokens;
	return (ERR_NONE);
}

static unsigned char	obj_face_loader(t_env *env, char **tokens)
{
	(void)env;
	(void)tokens;
	return (ERR_NONE);
}

///////////////////////////////////////////////////////////////////////////////

static unsigned char	obj_loader(t_env *env, char *line)
{
	unsigned char	(*obj_loading_fts[OBJ_MAX])(t_env *, char **) = {
												[OBJ_COMMENT] = NULL,
												[OBJ_MTLLIB] = obj_mtllib_loader,
												[OBJ_OBJECT_NAME] = obj_object_name_loader,
												[OBJ_VERTEX] = obj_vertex_loader,
												[OBJ_USEMTL] = obj_usemtl_loader,
												[OBJ_FACE] = obj_face_loader,
												[OBJ_SMOOTH_SHADING] = NULL};

	const char		*obj_lines_ids[OBJ_MAX] = { [OBJ_COMMENT] = "#",
												[OBJ_MTLLIB] = "mtllib",
												[OBJ_OBJECT_NAME] = "o",
												[OBJ_VERTEX] = "v",
												[OBJ_USEMTL] = "usemtl",
												[OBJ_FACE] = "f",
												[OBJ_SMOOTH_SHADING] = "s"};
	char			**tokens;

	if (!(tokens = ft_strsplit(line, "\b\t\v\f\r ")))
		return (ERR_MALLOC_FAILED);

	for (unsigned int i = 0; i < OBJ_MAX; i++)
		if (ft_strcmp(tokens[0], obj_lines_ids[i]) == 0)
		{
			ft_free_ctab(tokens);
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
