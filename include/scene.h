#ifndef SCENE_H
# define SCENE_H

# define OBJ_SPEED 0.1f

typedef	struct	s_mesh
{
	t_dynarray	faces;
	t_vec3d		o;
	char		pad[4];
	char		*name;
}				t_mesh;

typedef	struct		s_color
{
	float	r;
	float	g;
	float	b;
	float	a;
}					t_color;

typedef struct		s_texture
{
	unsigned char	*img_data;
	int				w;
	int				h;
}					t_texture;

typedef	struct		s_mtl
{
	t_texture		texture;
	t_color			color;
	char			*name;
}					t_mtl;

typedef	struct	s_face
{
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	int16_t		mtl;
	int16_t		pad;
}				t_face;

typedef struct	s_scene
{
	t_dynarray	meshs;
	t_dynarray	vertexs;
	t_dynarray	faces;
	t_dynarray	mtls;
	uint32_t	*indices;
}				t_scene;

#endif
