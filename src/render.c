#include "main.h"

/****************************************************************
 * The glfwWindowShouldClose function checks at the start of each
 loop iteration if GLFW has been instructed to close. If so,
 the function returns true and the render loop stops running, after
 which we can close the application.
 * The glfwPollEvents function checks if any events are triggered
 (like keyboard input or mouse movement events), updates the
 window state, and calls the corresponding functions (which we
 can register via callback methods).
 * The glfwSwapBuffers will swap the color buffer (a large 2D
 buffer that contains color values for each pixel in GLFW's
 window) that is used to render to during this render iteration
 and show it as output to the screen.
****************************************************************/

/************************************************************
glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
************************************************************/

static void				pipeline(t_env *env)
{
	t_vec3d	*v;

	memcpy(env->scene.p_vertexs.c, env->scene.vertexs.c, sizeof(t_vec3d) * (unsigned long)env->scene.vertexs.nb_cells);

	for (int i = 0; i < env->scene.p_vertexs.nb_cells; i++)
	{
		v = dyacc(&env->scene.p_vertexs, i);
		*v = matrix_mult_vec(env->scene.cam.mats.w_m, *v);
	}

	for (int i = 0; i < env->scene.p_vertexs.nb_cells; i++)
	{
		v = dyacc(&env->scene.p_vertexs, i);
		*v = matrix_mult_vec(env->scene.cam.mats.v_m, *v);
	}

	for (int i = 0; i < env->scene.p_vertexs.nb_cells; i++)
	{
		v = dyacc(&env->scene.p_vertexs, i);
		*v = matrix_mult_vec(env->scene.cam.mats.p_m, *v);
	}
}

static unsigned char	render_scene(t_env *env)
{
	GLsizeiptr	size;
	t_mesh		*m;

	compute_view_matrix(env);
	compute_rotation_matrix(env);

	pipeline(env);

	size = (GLsizeiptr)sizeof(t_vec3d) * env->scene.p_vertexs.nb_cells;
	glBufferData(GL_ARRAY_BUFFER, size, env->scene.p_vertexs.c, GL_STATIC_DRAW);

	// Launch shaders-composed program
	glUseProgram(env->shader_program);

//	int mvp_loc = glGetUniformLocation(env->vertex_shader_id, "mvp");
//	glUniformMatrix4fv(mvp_loc, 1, GL_TRUE, env->scene.cam.mats.flat_mvp);

	// Draw triangles by faces indices contained in faces data structure
	glDrawElements(GL_TRIANGLES, env->scene.faces.nb_cells * 3, GL_UNSIGNED_INT, 0);

	if (env->settings.rotation)
	{
		m = dyacc(&env->scene.meshs, 0);
		rotate_mesh(env, m->o, 0.01f, rotate_y);
	}
	return (ERR_NONE);
}

unsigned char   display_loop(t_env *env)
{
	unsigned char	code;

	// set clearcolor to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Main rendering loop
    while (!glfwWindowShouldClose(env->window))
    {
        // Events handler
        processInput(env->window);

		// Clear the screen and the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		// Rendering
		if ((code = render_scene(env)) != ERR_NONE)
			return (code);

		// Update window's content
        glfwSwapBuffers(env->window);
        glfwPollEvents();
    }

    glfwTerminate();
    return (ERR_NONE);
}
