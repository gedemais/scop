#ifndef SCENE_H
# define SCENE_H

typedef	struct	s_mesh
{
	t_dynarray	faces;
	t_vec3d		o;
	char		*name;
}				t_mesh;

typedef	struct	s_face
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint16_t	mtl;
	uint16_t	pad;
}				t_face;

typedef struct	s_scene
{
	t_dynarray	meshs;
	t_dynarray	vertexs;
	t_dynarray	faces;
}				t_scene;

#endif
