#include "Application.h"
#include <iostream>
#include "ShaderFuncs.h"


Application::Application() : oPlane()
{

}

void Application::setupGeometry()
{
	oPlane.createPlane(5);

	glGenVertexArrays(1, &oPlane.vao);
	glBindVertexArray(oPlane.vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, oPlane.getVertexSizeInBytes() +
		oPlane.getTextureCoordsSizeInBytes(), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, oPlane.getVertexSizeInBytes(), oPlane.plane);

	glBufferSubData(GL_ARRAY_BUFFER, oPlane.getVertexSizeInBytes(),
		oPlane.getTextureCoordsSizeInBytes(), oPlane.textureCoords);

	oPlane.cleanMemory();

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(oPlane.getVertexSizeInBytes()));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnable(GL_DEPTH_TEST);

	//ids["triangle"] = VAO;

}


void Application::setupProgram()
{
	std::string vertexShader = loadTextFile("shaders/VertexADS.glsl");
	std::string fragmentShader = loadTextFile("shaders/FragmentADS.glsl");
	ids["program"] = InitializeProgram(vertexShader, fragmentShader);
	//ids["time"] = glGetUniformLocation(ids["program"], "time");
	ids["camera"] = glGetUniformLocation(ids["program"], "camera");
	ids["projection"] = glGetUniformLocation(ids["program"], "projection");
}

void Application::keyCallback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Application::setup()
{
	setupGeometry();
	setupProgram();
	projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 100.0f);
}

void Application::update()
{
	time += 0.01f;
	eye = glm::vec3( 0.0f, 3.0f, 5.0f);
	center = glm::vec3(0.01f, 0.01f, 0.01f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	camera = glm::lookAt(eye, center, up);
}

void Application::draw()
{
	//Seleccionar programa (shaders)
	glUseProgram(ids["program"]);

	//Pasar el resto de los parámetros para el programa
	//glUniform1f(ids["time"], time);
	glUniformMatrix4fv(ids["camera"],1 , GL_FALSE, &camera[0][0]);
	glUniformMatrix4fv(ids["projection"], 1, GL_FALSE, &projection[0][0]);
	
	//Seleccionar la geometria (el triangulo)
	//glBindVertexArray(ids["triangle"]);
	glBindVertexArray(oPlane.vao);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glDraw()
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());
}
