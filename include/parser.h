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

enum	e_obj_lines_id
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
	MTL_MAX
};

#endif
