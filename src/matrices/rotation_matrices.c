#include "main.h"

void	update_xrotation_matrix(float m[4][4], float theta)
{
	float	c;
	float	s;

	c = cosf(theta);
	s = sinf(theta);
	m[0][0] = 1.0f;
	m[1][1] = c;
	m[1][2] = -s;
	m[2][1] = s;
	m[2][2] = c;
	m[3][3] = 1.0f;
}

void	update_yrotation_matrix(float m[4][4], float theta)
{
	float	c;
	float	s;

	c = cosf(theta);
	s = sinf(theta);
	m[0][0] = c;
	m[0][2] = s;
	m[1][1] = 1.0f;
	m[2][0] = -s;
	m[2][2] = c;
	m[3][3] = 1.0f;
}

void	update_zrotation_matrix(float m[4][4], float theta)
{
	float	c;
	float	s;

	c = cosf(theta);
	s = sinf(theta);
	m[0][0] = c;
	m[0][1] = s;
	m[1][0] = -s;
	m[1][1] = c;
	m[2][2] = 1.0f;
	m[3][3] = 1.0f;
}
