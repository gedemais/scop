#include "main.h"

static unsigned char	scop(t_env *env, int argc, char **argv)
{
	unsigned char	code;

	if ((code = init(env, argc, argv)) != ERR_NONE)
		return (code);
	return (ERR_NONE);
}

int						main(int argc, char **argv)
{
	t_env			env;
	unsigned char	code;

	memset(&env, 0, sizeof(t_env));
	if ((code = scop(&env, argc, argv)) != ERR_NONE)
	{
		error_handler(&env, code);
		return (code);
	}

//	printf("---------------------- Vertexs ----------------------\n");
//	t_vec3d	*v;
//	for (unsigned int i = 0; (int)i < env.scene.vertexs.nb_cells; i++)
//	{
//		v = dyacc(&env.scene.vertexs, (int)i);
//		printf("%f %f %f %f\n", (double)v->x, (double)v->y, (double)v->z, (double)v->w);
//	}
//
//	printf("---------------------- Faces ----------------------\n");
//	t_face	*f;
//	for (unsigned int i = 0; (int)i < env.scene.faces.nb_cells; i++)
//	{
//		f = dyacc(&env.scene.faces, (int)i);
//		printf("%d %d %d\n", f->a, f->b, f->c);
//	}
//
//	
//	printf("---------------------- Mesh ----------------------\n");
//	t_mesh		*m = dyacc(&env.scene.meshs, 0);
//	uint32_t	*index;
//	for (unsigned int i = 0; (int)i < m->faces.nb_cells; i++)
//	{
//		index = dyacc(&m->faces, (int)i);
//		assert(index == )
//		printf("%u\n", *index);
//	}

	return (ERR_NONE);
}
