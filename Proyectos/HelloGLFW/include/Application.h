#pragma once
#include <glad.h>
#include <iostream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "GLFW/glfw3.h"

class Application
{
private:



public:

	GLFWwindow* window;


	void setup();
	void update();
	void draw();


	void keyCallback(int key, int scancode, int action, int mods);

};
