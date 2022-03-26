#include "main.h"

unsigned char	mtl_newmtl_loader(t_env *env, char **tokens)
{
	t_mtl	new; // New material object

	ft_memset(&new, 0, sizeof(t_mtl));
	if (ft_tablen(tokens) != 2) // Syntax check
		return (ERR_INVALID_NEWMTL_INSTRUCTION);

	if (!(new.name = ft_strdup(tokens[1])) // Copies material name
		// Initializes materials pool if not already up
		|| (env->scene.mtls.c == NULL && init_dynarray(&env->scene.mtls, sizeof(t_mtl), 1)))
		return (ERR_MALLOC_FAILED);

	// Moves the new material in the pool
	if (push_dynarray(&env->scene.mtls, &new, false))
		return (ERR_MALLOC_FAILED);

	return (ERR_NONE);
}

unsigned char	mtl_diffuse_color_loader(t_env *env, char **tokens)
{
	t_mtl	*mtl; // Material to apply color at

	if (ft_tablen(tokens) != 4) // Syntax check
		return (ERR_INVALID_KD_INSTRUCTION);

	if (env->scene.mtls.c == NULL) // Checks for existing material(s) to apply color at
		return (ERR_NO_DEFINED_MTL_FOR_KD);

	mtl = dyacc(&env->scene.mtls, env->scene.mtls.nb_cells - 1);

	// Reads color rgb components
	mtl->color.r = (float)atof(tokens[1]);
	mtl->color.g = (float)atof(tokens[2]);
	mtl->color.b = (float)atof(tokens[3]);

	// RGB values check
	if (mtl->color.r < 0.0f || mtl->color.r > 1.0f
		|| mtl->color.g < 0.0f || mtl->color.g > 1.0f
		|| mtl->color.b < 0.0f || mtl->color.b > 1.0f)
		return (ERR_INVALID_RGB_VALUE_FOR_KD_INSTRUCTION);

	return (ERR_NONE);
}

unsigned char	mtl_alpha_component_loader(t_env *env, char **tokens)
{
	t_mtl	*mtl; // Material to apply color at

	if (ft_tablen(tokens) != 2) // Syntax check
		return (ERR_INVALID_D_INSTRUCTION);

	if (env->scene.mtls.c == NULL) // Checks for existing material(s) to apply color at
		return (ERR_NO_DEFINED_MTL_FOR_D);

	mtl = dyacc(&env->scene.mtls, env->scene.mtls.nb_cells - 1);

	// Reads alpha value
	mtl->color.a = (float)atof(tokens[1]); // 0 - 1 (1 : no transparency)

	// Checks alpha value
	if (mtl->color.a < 0.0f || mtl->color.a > 1.0f)
		return (ERR_INVALID_ALPHA_VALUE);

	return (ERR_NONE);
}

static char		*make_texture_path(t_env *env, char *filename)
{
	char		 *path; // Returned string containing texture file path
	unsigned int i = 0;

	while (env->obj_path[i] && env->obj_path[i] != '/') // Find slash in the string
		i++;

	if (env->obj_path[i] == '/') // If there is one, we stop the string after it.
	{
		i++;
		env->obj_path[i] = 0;
	}
	else // Else, we set the string at empty to allow us to strjoin in both ways
		env->obj_path[0] = 0;

	if (!(path = ft_strjoin(env->obj_path, filename)))
		return (NULL);

	return (path);
}

unsigned char	mtl_texture_image_loader(t_env *env, char **tokens)
{
	t_mtl			*mtl; // Pointer used for syntaxic contraction
	t_texture		*txt; // Texture pointer
	char			*path; // Image file path string
	unsigned int	i = 0;

	if (ft_tablen(tokens) != 2) // Syntaxic check
		return (ERR_INVALID_MAP_KD_INSTRUCTION);

	while (tokens[1][i] && tokens[1][i] != '.') // Find a dot in the filename
		i++;

	if (tokens[1][i] == 0 || ft_strcmp(&tokens[1][i], ".bmp")) // File extension check
		return (ERR_INCOMPATIBLE_TEXTURE_FILE);

	if (!(path = make_texture_path(env, tokens[1]))) // Create total relative path
		return (ERR_MALLOC_FAILED);

	mtl = dyacc(&env->scene.mtls, env->scene.mtls.nb_cells - 1);
	txt = &mtl->texture;

	if (loadBMP(path, &txt->img_data, &txt->w, &txt->h)) // Load image from path
	{
		free(path);
		return (ERR_COULD_NOT_LOAD_BMP_FILE);
	}
	free(path); // Free path string
	return (ERR_NONE);
}
