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

static unsigned char	render_scene(t_env *env)
{
	GLsizeiptr	size;
	//t_mesh		*m;
	static float	angle = 0.0f;

	compute_rotation_matrix(env);

	size = (GLsizeiptr)sizeof(t_stride) * env->scene.vertexs.nb_cells;
	glBufferData(GL_ARRAY_BUFFER, size, env->scene.vertexs.c, GL_STATIC_DRAW);
	//glBindVertexArray(env->vbo);

	update_yrotation_matrix(env->scene.cam.mats.ry_m, (float)ft_to_radians((double)angle));
	matrix_flattener(env->scene.cam.mats.ry_m, env->scene.cam.mats.flat_mvp);

	// Launch shaders-composed program
	glUseProgram(env->shader_program);

	int mvp_loc = glGetUniformLocation(env->shader_program, "mvp");
	printf("%d\n", mvp_loc);
	glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, env->scene.cam.mats.flat_mvp);

	// Draw triangles
	glDrawArrays(GL_TRIANGLES, 0, env->scene.vertexs.nb_cells);

	if (env->settings.rotation)
		angle += (float)env->settings.rotation_speed / 10.0f;

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
