#include "main.h"

static int		left_quarters(t_env *env, int x, int y, int hwdt, int hhgt)
{
	t_cam	*cam;
	float	ratio;

	cam = &env->scene.cam;
	ratio = cam->aspect_ratio;
	if (x <= hwdt && y < hhgt)
	{
		cam->yaw -= fabs((hwdt - x) * SENSI) * ratio;
		if (cam->pitch - fabs((hhgt - y) * SENSI) >= -90)
			cam->pitch -= fabs((hhgt - y) * SENSI);
		return (1);
	}
	else if (x < hwdt && y >= hhgt)
	{
		cam->yaw -= fabs((hwdt - x) * SENSI) * ratio;
		if (cam->pitch + fabs((hhgt - y) * SENSI) <= 90)
			cam->pitch += fabs((hhgt - y) * SENSI);
		return (1);
	}
	return (0);
}

static int		right_quarters(t_env *env, int x, int y, int hwdt, int hhgt)
{
	t_cam	*cam;
	float	ratio;

	cam = &env->scene.cam;
	ratio = cam->aspect_ratio;
	if (x >= hwdt && y < hhgt)
	{
		cam->yaw += fabs((hwdt - x) * SENSI) * ratio;
		if (cam->pitch - fabs((hhgt - y) * SENSI) >= -90)
			cam->pitch -= fabs((hhgt - y) * SENSI);
		return (1);
	}
	else if (x > hwdt && y >= hhgt)
	{
		cam->yaw += fabs((hwdt - x) * SENSI) * ratio;
		if (cam->pitch + fabs((hhgt - y) * SENSI) <= 90)
			cam->pitch += fabs((hhgt - y) * SENSI);
		return (1);
	}
	return (0);
}

void			camera_aim(t_env *env)
{
	double	mouse_x;
	double	mouse_y;
	int		hwdt;
	int		hhgt;

	hwdt = env->settings.w_wdt / 2;
	hhgt = env->settings.w_hgt / 2;
	glfwGetCursorPos(env->window, &mouse_x, &mouse_y);
	if (!left_quarters(env, (int)mouse_x, (int)mouse_y, hwdt, hhgt))
		right_quarters(env, (int)mouse_x, (int)mouse_y, hwdt, hhgt);

	glfwSetCursorPos(env->window, hwdt, hhgt);
}
