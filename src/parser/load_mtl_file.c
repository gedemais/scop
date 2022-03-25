#include "main.h"

// Constant array of strings used to store mtl format line identifiers.
static const char		*mtl_lines_ids[MTL_MAX] = {
									  [MTL_COMMENT] = "#",
									  [MTL_NEWMTL] = "newmtl",
									  [MTL_Ns] = "Ns",
									  [MTL_Ka] = "Ka",
									  [MTL_Kd] = "Kd",
									  [MTL_Ks] = "Ks",
									  [MTL_Ni] = "Ni",
									  [MTL_d] = "d",
									  [MTL_ILLUM] = "illum",
									  [MTL_MAP_KD] = "map_Kd"
};

// Function pointer array used to bind a function to each line identifier.
static unsigned char	(*mtl_loading_fts[MTL_MAX])(t_env *, char **) = {
									  [MTL_COMMENT] = NULL,
									  [MTL_NEWMTL] = mtl_newmtl_loader,
									  [MTL_Ns] = NULL,
									  [MTL_Ka] = mtl_ambient_color_loader,
									  [MTL_Kd] = NULL,
									  [MTL_Ks] = NULL,
									  [MTL_Ni] = NULL,
									  [MTL_d] = mtl_alpha_component_loader,
									  [MTL_ILLUM] = NULL,
									  [MTL_MAP_KD] = mtl_texture_image_loader
};

static unsigned char	mtl_loader(t_env *env, char *line)
{
	char	**tokens;

	if (!(tokens = ft_strsplit(line, "\b\t\v\f\r ")))
		return (ERR_MALLOC_FAILED);

	for (unsigned int i = 0; i < MTL_MAX; i++)
		if (ft_strcmp(tokens[0], mtl_lines_ids[i]) == 0)
			return (mtl_loading_fts[i] ? mtl_loading_fts[i](env, tokens) : ERR_NONE);

	return (ERR_NONE);
}

static unsigned char	load_mtl_file(t_env *env)
{
	char			**lines;
	unsigned char	code;

	if ((code = readlines(env->obj_path, &lines)) != ERR_NONE)
		return (code);

	for (unsigned int i = 0; lines[i]; i++)
		if ((code = mtl_loader(env, lines[i])))
			return (code);

	ft_free_ctab(lines);
	return (ERR_NONE);
}

unsigned char	obj_mtllib_loader(t_env *env, char **tokens)
{
	unsigned char	code;

	/* Making new path, assuming that mtl file is named the same as its
	 * corresponding obj file, and is located in the same directory.*/
	(void)tokens;
	ft_strcpy(&env->obj_path[ft_strlen(env->obj_path) - 4], ".mtl");

	if ((code = load_mtl_file(env)) != ERR_NONE)
		return (code);

	return (ERR_NONE);
}
