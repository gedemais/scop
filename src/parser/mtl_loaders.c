#include "main.h"

unsigned char	mtl_newmtl_loader(t_env *env, char **tokens)
{
	t_mtl	new;

	ft_memset(&new, 0, sizeof(t_mtl));
	if (ft_tablen(tokens) != 2)
		return (ERR_INVALID_NEWMTL_INSTRUCTION);

	if (!(new.name = ft_strdup(tokens[1]))
		|| (env->scene.mtls.c == NULL && init_dynarray(&env->scene.mtls, sizeof(t_mtl), 1)))
		return (ERR_MALLOC_FAILED);

	if (push_dynarray(&env->scene.mtls, &new, false))
		return (ERR_MALLOC_FAILED);

	return (ERR_NONE);
}

unsigned char	mtl_ambient_color_loader(t_env *env, char **tokens)
{
	t_mtl	*mtl;

	if (ft_tablen(tokens) != 4)
		return (ERR_INVALID_KA_INSTRUCTION);

	if (env->scene.mtls.c == NULL)
		return (ERR_NO_DEFINED_MTL_FOR_KA);

	mtl = dyacc(&env->scene.mtls, env->scene.mtls.nb_cells - 1);

	mtl->color.r = (float)atof(tokens[1]);
	mtl->color.g = (float)atof(tokens[2]);
	mtl->color.b = (float)atof(tokens[3]);

	return (ERR_NONE);
}

unsigned char	mtl_alpha_component_loader(t_env *env, char **tokens)
{
	(void)env;
	(void)tokens;
	printf("%s\n", __FUNCTION__);
	return (ERR_NONE);
}

unsigned char	mtl_texture_image_loader(t_env *env, char **tokens)
{
	(void)env;
	(void)tokens;
	printf("%s\n", __FUNCTION__);
	return (ERR_NONE);
}

