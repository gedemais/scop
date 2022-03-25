#ifndef SCENE_H
# define SCENE_H

typedef	struct	s_mesh
{
	t_dynarray	faces;
	t_vec3d		o;
	char		*name;
}				t_mesh;

typedef	struct		s_color
{
	float	r;
	float	g;
	float	b;
	float	a;
}					t_color;

typedef	struct		s_mtl
{
	t_color			color;
	char			*name; // Name
	char			**texture; // Images data arrays. NULL if no texture.
}					t_mtl;

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
	t_dynarray	mtls;
}				t_scene;

#endif
