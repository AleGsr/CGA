#include "Application.h"
#include <iostream>
#include "ShaderFuncs.h"
//#include “glm/gtc/type_ptr.hpp”



Application::Application() : oPlane()
{

}


void Application::setupGeometry()
{
	oPlane.createPlane(100);

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

void Application::setupProgram1()
{
	std::string vertexShader = loadTextFile("shaders/VertexShader.glsl");
	std::string fragmentShader = loadTextFile("shaders/FragmentShader.glsl");
	ids["program1"] = InitializeProgram(vertexShader, fragmentShader);
	ids["time1"] = glGetUniformLocation(ids["program1"], "time");
}

void Application::setupProgram2()
{
	std::string vertexShader = loadTextFile("shaders/VertexADS.glsl");
	std::string fragmentShader = loadTextFile("shaders/FragmentADS.glsl");
	ids["program2"] = InitializeProgram(vertexShader, fragmentShader);
	ids["time2"] = glGetUniformLocation(ids["program2"], "time");
	ids["camera"] = glGetUniformLocation(ids["program2"], "camera");
	ids["projection"] = glGetUniformLocation(ids["program2"], "projection");
}

void Application::keyCallback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//teclas para mover	
}

void Application::setup()
{
	setupGeometry();
	setupProgram1();
	setupProgram2();
	projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 100.0f);


	//Valores del uniform
	/*glUniform4fv(LightPosition, 1, glm::value_ptr(light.position));
	glUniform4fv(LightAmbient, 1, glm::value_ptr(light.ambient));
	glUniform4fv(LightDiffuse, 1, glm::value_ptr(light.diffuse));
	glUniform4fv(LightSpecular, 1, glm::value_ptr(light.specular));


	glUniform4fv(MaterialAmbien, 1, glm::value_ptr(material.ambient));
	glUniform4fv(MaterialDiffuse, 1, glm::value_ptr(material.diffuse));
	glUniform4fv(MaterialSpecular, 1, glm::value_ptr(material.specular));*/

}

void Application::update()
{
	time += 0.1f;
	eye = glm::vec3( 0.0f, 3.0f, 3.0f);
	camera = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Application::draw()
{
	//Seleccionar programa (shaders)
	glUseProgram(ids["program2"]);

	//Pasar el resto de los parámetros para el programa
	glUniform1f(ids["time2"], time);
	glUniformMatrix4fv(ids["camera"],1 , GL_FALSE, &camera[0][0]);
	glUniformMatrix4fv(ids["projection"], 1, GL_FALSE, &projection[0][0]);



	//Ids
	 //Light
	GLint LightPosition = glGetUniformLocation(ids["program2"], "light.position");
	GLint LightAmbient = glGetUniformLocation(ids["program2"], "light.ambient");
	GLint LightDiffuse = glGetUniformLocation(ids["program2"], "light.diffuse");
	GLint LightSpecular = glGetUniformLocation(ids["program2"], "light.specular");

	 //Material
	GLint MaterialAmbient = glGetUniformLocation(ids["program2"], "material.ambient");
	GLint MaterialDiffuse = glGetUniformLocation(ids["program2"], "material.diffuse");
	GLint MaterialSpecular = glGetUniformLocation(ids["program2"], "material.specular");


	
	//Seleccionar la geometria (el triangulo)
	//glBindVertexArray(ids["triangle"]);
	glBindVertexArray(oPlane.vao);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glDraw()
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());


}
