#include "main.h"

static void	assign_face_indexes(t_face *new, char **tokens, int indexes[3])
{
	// Reads the faces components (indexes in vertexs pool)
	new->a = (int32_t)ft_atoi(tokens[indexes[0]]) - 1;
	new->b = (int32_t)ft_atoi(tokens[indexes[1]]) - 1;
	new->c = (int32_t)ft_atoi(tokens[indexes[2]]) - 1;
}

static unsigned char	check_face_indexes(t_env *env, t_face new)
{
	// Checks if vertexs indexes values are coherent with the rest of the file
	if (new.a < 0 || new.a >= env->scene.vertexs.nb_cells
		|| new.b < 0 || new.b >= env->scene.vertexs.nb_cells
		|| new.c < 0 || new.c >= env->scene.vertexs.nb_cells)
		return (ERR_INVALID_VERTEX_INDEX_FOR_FACE);
	return (ERR_NONE);
}

static unsigned char	split_quad(t_env *env, t_mesh *parent, uint32_t a_index, char **tokens)
{
	t_face		news[2];
	uint32_t	b_index = a_index + 1;

	ft_memset(news, 0, sizeof(t_face) * 2);
	// Polygon faces indexes assignment
	assign_face_indexes(&news[0], tokens, (int[3]){1, 2, 3});
	assign_face_indexes(&news[1], tokens, (int[3]){1, 3, 4});

	// Checks indexes values
	if (check_face_indexes(env, news[0]) != ERR_NONE
		|| check_face_indexes(env, news[1]) != ERR_NONE)
		return (ERR_INVALID_VERTEX_INDEX_FOR_FACE);

	// Moves new faces into pool
	if (push_dynarray(&env->scene.faces, &news[0], false)
		|| push_dynarray(&env->scene.faces, &news[1], false))
		return (ERR_MALLOC_FAILED);

	// Moves faces indexes into parent mesh
	if (push_dynarray(&parent->faces, &a_index, false)
		|| push_dynarray(&parent->faces, &b_index, false))
		return (ERR_MALLOC_FAILED);

	return (ERR_NONE);
}

static unsigned char	load_face(t_env *env, char **tokens, t_mesh *parent, uint32_t face_index)
{
	t_face	new;

	ft_memset(&new, 0, sizeof(t_face));
	new.mtl = used_mtl; // Material assignment
	assign_face_indexes(&new, tokens, (int[3]){1, 2, 3});

	// Moves instance in the pool.
	if (push_dynarray(&env->scene.faces, &new, false)
		// Moves instance's pool index in the parent mesh.
		|| push_dynarray(&parent->faces, &face_index, false)) 
		return (ERR_MALLOC_FAILED);
	// Negative / pool bound test.
	return (check_face_indexes(env, new));
}

unsigned char	obj_face_loader(t_env *env, char **tokens)
{
	t_mesh			*parent; // Mesh composed by the face
	uint32_t		face_index; // Index of the instance in the faces pool
	uint32_t		nb_vertexs; // Number of vertexs of the face line
	unsigned char	code;

	if (!(parent = dyacc(&env->scene.meshs, (int)current_mesh))
		&& (code = create_default_mesh(env)))
		return (code);

	parent = dyacc(&env->scene.meshs, (int)current_mesh);
	face_index = (uint32_t)env->scene.faces.nb_cells;
	nb_vertexs = (uint32_t)ft_tablen(tokens) - 1;

	if (env->scene.faces.c == NULL // Initialization of faces pool
		&& init_dynarray(&env->scene.faces, sizeof(t_face), 256))
		return (ERR_MALLOC_FAILED);

	if (nb_vertexs == 3) // If the face is a polygon
		return (load_face(env, tokens, parent, face_index));
	else if (nb_vertexs == 4) // Transforms quad faces to polygons, and moves them into the faces pool
		return (split_quad(env, parent, face_index, tokens));
	// If this kind of face is not handled
	return (ERR_INVALID_PRIMITIVE_DESCRIPTION);
}
