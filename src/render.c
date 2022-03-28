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

static void		render_scene(t_env *env)
{
	(void)env;
}

unsigned char   display_loop(t_env *env)
{

    while (!glfwWindowShouldClose(env->window))
    {
        // Events handler
        processInput(env->window);

		render_scene(env);

        glfwSwapBuffers(env->window);
        glfwPollEvents();
    }

    glfwTerminate();
    return (ERR_NONE);
}
