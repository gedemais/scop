#include "main.h"

void	rotate_mesh(t_env *env)
{
	(void)env;
}

static void	translate_mesh(t_env *env, t_vec3d translation)
{
	t_vec3d		translated;
	t_vec3d		*v;
	int			i = 0;

	// There is normally only one mesh in the scene, so let's just
	// translate all vertices the same way.
	while (i < env->scene.vertexs.nb_cells)
	{
		v = dyacc(&env->scene.vertexs, i);
		translated = vec_add(*v, translation);
		ft_memcpy(v, &translated, sizeof(t_vec3d));
		i++;
	}
}

// Moves directions :

void	move_object(t_env *env, int key)
{
	GLsizeiptr		size;
	t_vec3d	tst = (t_vec3d){0.0f, 0.0f, 0.0f};

	if (key == env->settings.keys[KEY_MOVE_OBJECT_UP])
		tst = vec_add(tst, (t_vec3d){0.0f, OBJ_SPEED, 0.0f});
	if (key == env->settings.keys[KEY_MOVE_OBJECT_DOWN])
		tst = vec_add(tst, (t_vec3d){0.0f, -OBJ_SPEED, 0.0f});
	if (key == env->settings.keys[KEY_MOVE_OBJECT_LEFT])
		tst = vec_add(tst, (t_vec3d){-OBJ_SPEED, 0.0f, 0.0f});
	if (key == env->settings.keys[KEY_MOVE_OBJECT_RIGHT])
		tst = vec_add(tst, (t_vec3d){OBJ_SPEED, 0.0f, 0.0f});
	if (key == env->settings.keys[KEY_MOVE_OBJECT_FORWARD])
		tst = vec_add(tst, (t_vec3d){0.0f, 0.0f, -OBJ_SPEED});
	if (key == env->settings.keys[KEY_MOVE_OBJECT_BACKWARD])
		tst = vec_add(tst, (t_vec3d){0.0f, 0.0f, OBJ_SPEED});

	(void)key;
	translate_mesh(env, tst);
	size = (GLsizeiptr)sizeof(t_vec3d) * env->scene.vertexs.nb_cells;
	glBufferData(GL_ARRAY_BUFFER, size, env->scene.vertexs.c, GL_STATIC_DRAW);
}
