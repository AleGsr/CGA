
#pragma once
#include <vector>
#include <map>
#include "glad/glad.h"
#include <string>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <DirectXMath.h>
#include "Plane.h"

class Application
{
private:

	std::map<std::string, GLuint> ids;

	Plane oPlane;

	void setupGeometry();
	void setupProgram();
	GLuint setupTexture(const std::string& path);
	float mixerV{ 0.0f };
	float time{ 0.0f };
	float height{ 0.1f };
	glm::vec3 eye{ 0.0f, 0.0f, 2.0f };
	glm::mat4 camera;
	glm::mat4 projection;
	glm::mat4 model;
	glm::vec3 center{ 0.1f, 0.1f, 0.5f };


public:
	const int WINDOW_WIDTH = 1024;
	const int WINDOW_HEIGHT = 768;

	//Rotar 
	float moveHorizontal = 0.0f;
	float moveVertical = 0.0f;

	float zoom = 1.0f;
	float minScale = 0.5f;
	float maxScale = 3.0f;


	Application();
	GLFWwindow* window;
	void setup();
	void update();
	void draw();
	void keyCallback(int key, int scancode, int action, int mods);
	void mouseCallback(double xpos, double ypos);
	void ScrollCallback(double xoffset, double yoffset);
};