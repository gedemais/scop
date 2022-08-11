#include "main.h"

// Constant array of strings used to store obj format line identifiers.
static const char		*obj_lines_ids[OBJ_MAX] = {	[OBJ_COMMENT] = "#",
													[OBJ_MTLLIB] = "mtllib",
													[OBJ_OBJECT_NAME] = "o",
													[OBJ_VERTEX] = "v",
													[OBJ_VERTEX_TEXTURE] = "vt",
													[OBJ_USEMTL] = "usemtl",
													[OBJ_FACE] = "f",
													[OBJ_SMOOTH_SHADING] = "s"
};

// Functions prototypes are here to allow the function pointer array declaration below.
static unsigned char	obj_vertex_loader(t_env *env, char **tokens);
static unsigned char	obj_vertex_texture_loader(t_env *env, char **tokens);
static unsigned char	obj_object_name_loader(t_env *env, char **tokens);
static unsigned char	obj_usemtl_loader(t_env *env, char **tokens);

// Function pointer array used to bind a function to each line identifier.
static unsigned char	(*obj_loading_fts[OBJ_MAX])(t_env *, char **) = {
													[OBJ_COMMENT] = NULL, // NULL-set members are not handled
													[OBJ_MTLLIB] = obj_mtllib_loader,
													[OBJ_OBJECT_NAME] = obj_object_name_loader,
													[OBJ_VERTEX] = obj_vertex_loader,
													[OBJ_VERTEX_TEXTURE] = obj_vertex_texture_loader,
													[OBJ_USEMTL] = obj_usemtl_loader,
													[OBJ_FACE] = obj_face_loader,
													[OBJ_SMOOTH_SHADING] = NULL
};

////////////////////////////// Loading Functions //////////////////////////////

static unsigned char	obj_object_name_loader(t_env *env, char **tokens)
{
	t_dynarray	*meshs; // Pointer used for syntaxical contraction
	t_mesh		new; // Newly created mesh

	ft_memset(&new, 0, sizeof(t_mesh));
	new.o = (t_vec3d){0.0f, 0.0f, 0.0f, 0.0f};
	if (ft_tablen(tokens) != 2) // Format check
		return (ERR_INVALID_OBJECT_NAME);

	if (!(new.name = ft_strdup(tokens[1])) // Copies mesh's name
		|| init_dynarray(&new.faces, sizeof(uint32_t), 256)) // Initializes faces array in the new mesh object
		return (ERR_MALLOC_FAILED);

	meshs = &env->scene.meshs;
	if ((meshs->c == NULL && init_dynarray(meshs, sizeof(t_mesh), 1)) // Initializes meshes pool
		|| push_dynarray(meshs, &new, false)) // Moves the newly created mesh into the meshs pool
		return (ERR_MALLOC_FAILED);

	current_mesh = meshs->nb_cells - 1; // Updates current mesh affectation for vertexs and faces

	return (ERR_NONE);
}

static unsigned char	obj_vertex_loader(t_env *env, char **tokens)
{
	t_vec3d	new; // New vertex object

	ft_memset(&new, 0, sizeof(t_vec3d));
	if (ft_tablen(tokens) != 4) // Check format
		return (ERR_INVALID_VERTEX_FORMAT);

	if (env->scene.vertexs.c == NULL // Initialization of vertexs pool
		&& init_dynarray(&env->scene.vertexs, sizeof(t_vec3d), 256))
		return (ERR_MALLOC_FAILED);

	// Reads the three float components of the vertex
	new.x = (float)atof(tokens[1]);
	new.y = (float)atof(tokens[2]);
	new.z = (float)atof(tokens[3]);

	// Moves the newly created vertex into the vertexs pool
	if (push_dynarray(&env->scene.vertexs, &new, false))
		return (ERR_MALLOC_FAILED);

	return (ERR_NONE);
}

static unsigned char	obj_vertex_texture_loader(t_env *env, char **tokens)
{
	t_vt	new;

	ft_memset(&new, 0, sizeof(t_vt));
	if (ft_tablen(tokens) != 3) // Check format
		return (ERR_INVALID_VERTEX_TEXTURE_FORMAT);

	if (env->scene.vertexs_txt.c == NULL // Initialization of vertexs pool
		&& init_dynarray(&env->scene.vertexs_txt, sizeof(t_vt), 256))
		return (ERR_MALLOC_FAILED);

	new.u = (float)atof(tokens[1]);
	new.v = (float)atof(tokens[2]);

	// Moves the newly created vertex into the vertexs pool
	if (push_dynarray(&env->scene.vertexs_txt, &new, false))
		return (ERR_MALLOC_FAILED);

	return (ERR_NONE);
}

static unsigned char	obj_usemtl_loader(t_env *env, char **tokens)
{
	t_mtl	*mtl; // Pointer used to iterate through materials
	bool	found = false; // Triggers an error if the name given to usemtl is not found in materials pool

	if (ft_tablen(tokens) != 2) // Syntax check
		return (ERR_INVALID_SYNTAX_FOR_USEMTL_INSTRUCTION);

	for (int i = 0; i < env->scene.mtls.nb_cells; i++) // Iterates through mtls pool
	{
		mtl = dyacc(&env->scene.mtls, i); // Material pointer assignment
		printf("%s|%s\n", mtl->name, tokens[1]);
		if (ft_strcmp(mtl->name, tokens[1]) == 0) // Comparison with mtl name
		{
			found = true;
			printf("used_mtl = %d\n", i);
			used_mtl = (int16_t)i; // Update of currently used mtl
			printf("used_mtl = %d\n", used_mtl);
			break;
		}
	}

	if (!found)
		return (ERR_INVALID_NAME_FOR_USEMTL_INSTRUCTION);

	return (ERR_NONE);
}

static void				set_mesh_origin(t_env *env)
{
	t_mesh	*m;
	t_vec3d	*v;
	t_vec3d	acc = {0.0f, 0.0f, 0.0f, 0.0f};

	m = dyacc(&env->scene.meshs, 0);
	for (int i = 0; i < env->scene.vertexs.nb_cells; i++)
	{
		v = dyacc(&env->scene.vertexs, i);
		acc = vec_add(acc, *v);
	}
	m->o = vec_fdiv(acc, env->scene.vertexs.nb_cells);
	translate_mesh(env, vec_fmult(m->o, -1.0f));
}

///////////////////////////////////////////////////////////////////////////////

static unsigned char	obj_loader(t_env *env, char *line)
{
	char				**tokens;
	unsigned char		code;

	// Split the line in tokens by whitespaces.
	if (!(tokens = ft_strsplit(line, "\b\t\v\f\r ")))
		return (ERR_MALLOC_FAILED);

	// Identifies line type and lauches the corresponding loader.
	for (unsigned int i = 0; i < OBJ_MAX; i++)
		if (ft_strcmp(tokens[0], obj_lines_ids[i]) == 0)
		{
			// If this line indentifier is handled
			if (obj_loading_fts[i])
			{
				// Then launch the corresponding function
				code = obj_loading_fts[i](env, tokens);
				ft_free_ctab(tokens);
				return (code);
			}
			ft_free_ctab(tokens);
			return (ERR_NONE);
		}
	// Free tokens strings array
	ft_free_ctab(tokens);
	return (ERR_INVALID_OBJ_LINE_ID);
}

unsigned char	create_default_mesh(t_env *env)
{
	t_mesh	m; // New default mesh

	// Initializes mesh with default values
	m.o = (t_vec3d){0.0f, 0.0f, 0.0f, 0.0f};
	if (init_dynarray(&env->scene.meshs, sizeof(t_mesh), 1)
		|| !(m.name = ft_strdup("default"))
		|| init_dynarray(&m.faces, sizeof(uint32_t), 256))
		return (ERR_MALLOC_FAILED);

	// Adds the enterity of faces indexes to the mesh faces pool
	for (uint32_t i = 0; i < (uint32_t)env->scene.faces.nb_cells; i++)
		if (push_dynarray(&env->scene.faces, &i, false))
			return (ERR_MALLOC_FAILED);

	// Moves default mesh in meshs pool
	if (push_dynarray(&env->scene.meshs, &m, false))
		return (ERR_MALLOC_FAILED);

	// Updates current mesh index value
	current_mesh = env->scene.meshs.nb_cells - 1;

	return (ERR_NONE);
}

static unsigned char	gen_data_stride(t_env *env)
{
	t_dynarray	data; // New data stride array
	uint32_t	*f; // Pointers used to transfer data
	int			used;
	t_vec3d		*v;
	t_mtl		*m;
	t_stride	s; // New element

	printf("%d\n", env->scene.vertexs.nb_cells);
	if (init_dynarray(&data, sizeof(t_stride), env->scene.vertexs.nb_cells))
		return (ERR_MALLOC_FAILED);

	// Iterate through faces array
	for (int i = 0; i < env->scene.used_mtls.nb_cells; i++)
	{
		f = dyacc(&env->scene.faces, i); // Get face pointer
		// Get a pointer on the mtl used by the face

		used = *(int*)dyacc(&env->scene.used_mtls, i);
		printf("%d : %d\n", i, used);
		if (used < 0 || used > env->scene.used_mtls.nb_cells)
			used = 0;

		m = dyacc(&env->scene.mtls, used);
		// Create 3 strides for each faces and push them into the data array
		for (unsigned int j = 0; j < 3; j++)
		{
			v = dyacc(&env->scene.vertexs, (int)f[j]);
			memcpy(&s.v, v, sizeof(t_vec3d));
			memcpy(&s.c, &m->color, sizeof(t_color));

			if (push_dynarray(&data, &s, false))
				return (ERR_MALLOC_FAILED);
		}
	}

	// Replace vertexs array with data
	free_dynarray(&env->scene.vertexs);
	env->scene.vertexs = data;

	printf("%d\n", env->scene.vertexs.nb_cells);
	return (ERR_NONE);
}

unsigned char			load_obj_file(t_env *env, char *path)
{
	char			**lines;
	unsigned char	code;

	used_mtl = SHRT_MAX;
	current_mesh = INT_MAX;
	// Maps the .obj file in memory, then splits it into lines to parse it easier.
	if ((code = readlines(path, &lines)) != ERR_NONE)
		return (code);

	// Iterate through lines to load obj data.
	for (unsigned int i = 0; lines[i]; i++)
		if ((code = obj_loader(env, lines[i])) != ERR_NONE)
		{
			ft_free_ctab(lines);
			return (code);
		}

	// Creation of a default mesh to contain vertices and faces if not declared yet.
	if (env->scene.meshs.c == NULL && (code = create_default_mesh(env)) != ERR_NONE)
	{
		ft_free_ctab(lines);
		return (code);
	}
	ft_free_ctab(lines);

	// Normalize vertices for OpenGL display (i.e components between -1.0 and 1.0)
	normalize_vertexs(env);

	// Place the origin of the mesh on its center by averaging its vertexs
	set_mesh_origin(env);

	return (gen_data_stride(env));
}
