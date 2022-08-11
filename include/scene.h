#ifndef SCENE_H
# define SCENE_H

# define OBJ_SPEED 0.01f

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

typedef	struct		s_vertex_texture
{
	float	u;
	float	v;
}					t_vt;

typedef struct		s_stride
{
	t_vec3d		v;
	t_color		c;
	t_vt		t;
}					t_stride;

typedef struct		s_texture
{
	unsigned char	*img_data;
	unsigned int	gl_id;
	int				w;
	int				h;
	char			pad[4];
}					t_texture;

typedef	struct		s_material
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
}				t_face;

typedef struct	s_camera_matrices
{
	float		c_m[4][4];
	float		w_m[4][4];
	float		v_m[4][4];
	float		p_m[4][4];
	float		rx_m[4][4];
	float		ry_m[4][4];
	float		rz_m[4][4];
	float		crx_m[4][4];
	float		cry_m[4][4];
	float		cr_m[4][4];
	float		mvp[4][4];
	float		flat_mvp[16];
}				t_cam_mat;

typedef	struct	s_camera
{
	t_cam_mat	mats;
	t_vec3d		pos;
	t_vec3d		dir;
	t_vec3d		up;
	float		roll;
	float		pitch;
	float		yaw;
	float		aspect_ratio;
	float		fnear;
	float		ffar;
	float		fdelta;
	float		fovd;
	float		fovr;
	uint8_t		pad[4];
}				t_cam;

typedef struct	s_scene
{
	t_cam		cam;
	t_dynarray	meshs;
	t_dynarray	vertexs;
	t_dynarray	vertexs_txt;
	t_dynarray	faces;
	t_dynarray	used_mtls;
	t_dynarray	mtls;
	float		ct; // Color / Texture ratio
	uint8_t		pad[4];
}				t_scene;

#endif
