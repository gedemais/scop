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
	int32_t		a;
	int32_t		b;
	int32_t		c;
	int16_t		mtl;
	int16_t		pad;
}				t_face;

typedef struct	s_scene
{
	t_dynarray	meshs;
	t_dynarray	vertexs;
	t_dynarray	faces;
}				t_scene;

#endif
