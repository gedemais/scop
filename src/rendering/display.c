#include "glad.h"
#include <GLFW/glfw3.h>

/****************************************************************
The framebuffer size function takes a GLFWwindow as its first argument and two integers indicating the new window dimensions. Whenever the window changes in size, GLFW calls this function and fills in the proper arguments for you to process.
****************************************************************/

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    /****************************************************************
     * The first two parameters of glViewport set the location of the lower left corner of the window. The third and fourth parameter set the width and height of the rendering window in pixels, which we set equal to GLFW's window size.
     * We could actually set the viewport dimensions at values smaller than GLFW's dimensions; then all the OpenGL rendering would be displayed in a smaller window and we could for example display other elements outside the OpenGL viewport.
    ****************************************************************/

    glViewport(0, 0, width, height);
}

int init_display(t_env *env)
{
    t_settings *s;
    GLFWwindow *window;

    s = env->settings;

    /****************************************************************
     * We first initialize GLFW with glfwInit, after which we can configure GLFW using glfwWindowHint.
     * The first argument of glfwWindowHint tells us what option we want to configure, where we can select the option from a large enum of possible options prefixed with GLFW_.
     * The second argument is an integer that sets the value of our option. A list of all the possible options and its corresponding values can be found at GLFW's window handling documentation.
     * Note that on Mac OS X you need to add glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); to your initialization code for it to work.
    ****************************************************************/

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /****************************************************************
     * The glfwCreateWindow function requires the window width and height as its first two arguments respectively. The third argument allows us to create a name for the window. We can ignore the last 2 parameters.
     * The function returns a GLFWwindow object that we'll later need for other GLFW operations.
     * After that we tell GLFW to make the context of our window the main context on the current thread.
    ****************************************************************/

    window = glfwCreateWindow(s->w_wdt, s->w_hgt, "Scope", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return (ERR_FAILED_WIN);
    }
    glfwMakeContextCurrent(window);

    /****************************************************************
     * We pass GLAD the function to load the address of the OpenGL function pointers which is OS-specific.
     * GLFW gives us glfwGetProcAddress that defines the correct function based on which OS we're compiling for.
    ****************************************************************/

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return ERR_FAILED_GLAD;

    /****************************************************************
    We do have to tell GLFW we want to call this function on every window resize by registering it:
    ****************************************************************/

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /****************************************************************
     * The glfwWindowShouldClose function checks at the start of each loop iteration if GLFW has been instructed to close. If so, the function returns true and the render loop stops running, after which we can close the application.
     * The glfwPollEvents function checks if any events are triggered (like keyboard input or mouse movement events), updates the window state, and calls the corresponding functions (which we can register via callback methods).
     * The glfwSwapBuffers will swap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window) that is used to render to during this render iteration and show it as output to the screen.
    ****************************************************************/

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}