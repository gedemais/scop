#include "main.h"

// Constant array of strings used to store obj format line identifiers.
static const char		*obj_lines_ids[OBJ_MAX] = {	[OBJ_COMMENT] = "#",
													[OBJ_MTLLIB] = "mtllib",
													[OBJ_OBJECT_NAME] = "o",
													[OBJ_VERTEX] = "v",
													[OBJ_USEMTL] = "usemtl",
													[OBJ_FACE] = "f",
													[OBJ_SMOOTH_SHADING] = "s"
};

// Functions prototypes are here to allow the function pointer array declaration below.
static unsigned char	obj_vertex_loader(t_env *env, char **tokens);
static unsigned char	obj_object_name_loader(t_env *env, char **tokens);
static unsigned char	obj_usemtl_loader(t_env *env, char **tokens);

// Function pointer array used to bind a function to each line identifier.
static unsigned char	(*obj_loading_fts[OBJ_MAX])(t_env *, char **) = {
													[OBJ_COMMENT] = NULL, // NULL-set members are not handled
													[OBJ_MTLLIB] = obj_mtllib_loader,
													[OBJ_OBJECT_NAME] = obj_object_name_loader,
													[OBJ_VERTEX] = obj_vertex_loader,
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
	if (ft_tablen(tokens) != 2) // Format check
		return (ERR_INVALID_OBJECT_NAME);

	new.o = (t_vec3d){0.0, 0.0, 0.0, 0.0}; // Origin of the mesh in the scene
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

	ft_free_ctab(tokens); // Free tokens array
	return (ERR_NONE);
}

static unsigned char	obj_usemtl_loader(t_env *env, char **tokens)
{
	(void)env;
	(void)tokens;
	printf("%s\n", __FUNCTION__);
	return (ERR_NONE);
}

///////////////////////////////////////////////////////////////////////////////

static unsigned char	obj_loader(t_env *env, char *line)
{
	char				**tokens;

	// Split the line in tokens by whitespaces.
	if (!(tokens = ft_strsplit(line, "\b\t\v\f\r ")))
		return (ERR_MALLOC_FAILED);

	// Identifies line type and lauches the corresponding loader.
	for (unsigned int i = 0; i < OBJ_MAX; i++)
		if (ft_strcmp(tokens[0], obj_lines_ids[i]) == 0)
		{
			// Security check, if no objects are declared, then we can't add vertex or face.
			if ((i == OBJ_VERTEX || i == OBJ_FACE) && current_mesh == INT_MAX) // Initial value check
				return (ERR_NO_DEFINED_OBJECT);
			return (obj_loading_fts[i] ? obj_loading_fts[i](env, tokens) : ERR_NONE);
		}
	// Free tokens strings array
	ft_free_ctab(tokens);
	return (ERR_INVALID_OBJ_LINE_ID);
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
		if ((code = obj_loader(env, lines[i])))
			return (code);

	return (ERR_NONE);
}
