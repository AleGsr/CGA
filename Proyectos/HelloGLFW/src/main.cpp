#include "glad.h"
#include "GLFW/glfw3.h"
#include "Application.h"


Application app;

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    app.keyCallback(key, scancode, action, mods);
}


int main(void)
{

	/* Initialize the library */
	if (!glfwInit())
		return -1;

    /* Create a windowed mode window and its OpenGL context */
    app.window = glfwCreateWindow(1024, 768, "Hello Application", NULL, NULL);
    if (!app.window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(app.window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        //Manejar error
        return -1;
    }


    app.setup();

    glfwSetKeyCallback(app.window, KeyCallBack);


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    bool openWindow = true; //Variable que indica si va a estar abierta o no la ventana del proyecto

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(app.window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Swap front and back buffers */
        //glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        app.update();

        app.draw();

        /*Swap front and back buffers*/
        glfwSwapBuffers(app.window);
    }

    glfwTerminate();
    return 0;
}