#include "main.h"

static unsigned char	scop(t_env *env, int argc, char **argv)
{
	unsigned char	code;

	// Initialization
	if ((code = init(env, argc, argv)) != ERR_NONE)
		return (code);

	//exit(EXIT_SUCCESS); // chrono init time
	// Main loop launcher
	return (display_loop(env));
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

	//while(1);
	// Debugging prints
	if (DISPLAY_DATA)
	{
		printf("---------------------- Vertexs ----------------------\n");
		t_vec3d	*v;
		for (unsigned int i = 0; (int)i < env.scene.vertexs.nb_cells; i++)
		{
			v = dyacc(&env.scene.vertexs, (int)i);
			printf("%f %f %f %f\n", (double)v->x, (double)v->y, (double)v->z, (double)v->w);
		}

		printf("---------------------- Faces ----------------------\n");
		t_face	*f;
		for (unsigned int i = 0; (int)i < env.scene.faces.nb_cells; i++)
		{
			f = dyacc(&env.scene.faces, (int)i);
			printf("%d %d %d\n", f->a, f->b, f->c);
		}

		printf("---------------------- Mesh ----------------------\n");
		t_mesh		*m = dyacc(&env.scene.meshs, 0);
		uint32_t	*index;
		for (unsigned int i = 0; (int)i < m->faces.nb_cells; i++)
		{
			index = dyacc(&m->faces, (int)i);
			printf("%u\n", *index);
		}

		printf("---------------------- Materials ----------------------\n");
		t_mtl		*mtl;
		for (unsigned int i = 0; (int)i < env.scene.mtls.nb_cells; i++)
		{
			mtl = dyacc(&env.scene.mtls, (int)i);
			printf("%s :\nColor : R(%f) G(%f) B(%f) A(%f)\n",	mtl->name,
																(double)mtl->color.r,
																(double)mtl->color.g,
																(double)mtl->color.b,
																(double)mtl->color.a);
			if (mtl->texture.img_data)
				printf("Texture : %p\n------------------\n", (void*)mtl->texture.img_data);
		}
	}

	free_env(&env);

	return (ERR_NONE);
}
