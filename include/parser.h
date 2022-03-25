#ifndef PARSER_H
# define PARSER_H

enum	e_obj_lines_id
{
	OBJ_COMMENT,
	OBJ_MTLLIB,
	OBJ_OBJECT_NAME,
	OBJ_VERTEX,
	OBJ_USEMTL,
	OBJ_FACE,
	OBJ_SMOOTH_SHADING,
	OBJ_MAX
};

enum	e_mtl_lines_id
{
	MTL_COMMENT,
	MTL_NEWMTL,
	MTL_Ns,
	MTL_Ka,
	MTL_Kd,
	MTL_Ks,
	MTL_Ni,
	MTL_d,
	MTL_ILLUM,
	MTL_MAP_KD,
	MTL_MAX
};

/*
 * Globals keeping track of the index of the mesh we are currently
 * loading, and of which material is applied for currently loaded face.
 */
static int16_t	used_mtl;
static int32_t	current_mesh;

#endif
