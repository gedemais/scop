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

static void	update_mvp(t_env *env, t_cam *cam)
{
	// This function will compute model, view and projection matrices
	mat4_identity(cam->mats.model);
	mat4_translate(cam->mats.model, env->tst.x, env->tst.y, env->tst.z);
	mat4_rotate(cam->mats.model, env->rot.x, env->rot.y, env->rot.z);
	mat4_scale(cam->mats.model, 1.0f);

	mat4_view(cam);

	mat4_projection(cam->mats.projection, cam->fovd, cam->fnear, cam->ffar, cam->aspect_ratio);
}

static void	set_uniforms(t_env *env, t_cam *cam)
{
	// This function will set uniforms, which are variables usable into our shaders program.

	// Launch shaders-composed program
	glUseProgram(env->shader_program);

	glUniform1i(glGetUniformLocation(env->shader_program, "txt"),  (GLint)env->txt); // Texture ID
	glUniform1f(glGetUniformLocation(env->shader_program, "tc_ratio"),  (GLfloat)env->tc_ratio); // Texture-Color ratio

	// Matrices
	glUniformMatrix4fv(glGetUniformLocation(env->shader_program, "model"), 1, GL_FALSE, cam->mats.model);
	glUniformMatrix4fv(glGetUniformLocation(env->shader_program, "view"), 1, GL_FALSE, cam->mats.view);
	glUniformMatrix4fv(glGetUniformLocation(env->shader_program, "projection"), 1, GL_FALSE, cam->mats.projection);
}

static void				actions(t_env *env)
{
	// Rotation of the object on y axis
	if (env->settings.rotation)
		env->rot.y += (float)ft_to_radians((double)env->settings.rotation_speed / 10);

	// Color to object and object to color transitions (transparency value)
	if (env->settings.textured && env->tc_ratio < 1.0f)
		env->tc_ratio += env->settings.transition_speed / 1000.0f;
	else if (!env->settings.textured && env->tc_ratio > 0.0f)
		env->tc_ratio -= env->settings.transition_speed / 1000.0f;
	else
		env->tc_ratio = roundf(env->tc_ratio); // ratio used in fragment shader
}

static unsigned char	render_scene(t_env *env)
{
	static float	angle = 0.0f;

	update_mvp(env, &env->scene.cam);
	set_uniforms(env, &env->scene.cam);

	// Draw triangles with provided data stride and binded texture
	glDrawArrays(GL_TRIANGLES, 0, env->scene.vertexs.nb_cells);

	// Applies transformations according to user's inputs
	actions(env);

	return (ERR_NONE);
}

unsigned char   display_loop(t_env *env)
{
	unsigned char	code;

	// set clearcolor to black
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

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
