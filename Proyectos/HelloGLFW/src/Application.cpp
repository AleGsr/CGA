#include "Application.h"
#include <iostream>


void Application::setup()
{
}

void Application::update()
{
}

void Application::draw()
{
}

void Application::keyCallback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
