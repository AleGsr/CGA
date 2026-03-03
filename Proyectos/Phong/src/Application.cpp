#include "Application.h"
#include <iostream>
#include "ShaderFuncs.h"
#include "glm/gtc/type_ptr.hpp"


Application::Application() : oPlane()
{

}


void Application::setupGeometry()
{
	oPlane.createPlane(10);

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
	std::string vertexShader = loadTextFile("shaders/VertexPhong.glsl");
	std::string fragmentShader = loadTextFile("shaders/FragmentPhong.glsl");
	ids["program"] = InitializeProgram(vertexShader, fragmentShader);
	ids["time"] = glGetUniformLocation(ids["program"], "time");
	ids["camera"] = glGetUniformLocation(ids["program"], "camera");
	ids["model"] = glGetUniformLocation(ids["program"], "model");
	ids["projection"] = glGetUniformLocation(ids["program"], "projection");
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
	setupProgram();
	projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 100.0f);

	light.position = glm::vec3(1.0f, 0.5f, 0.01f);
	light.ambient = glm::vec4(0.01f, 1.2f, 0.01f, 1.0f);
	light.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	light.specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	material.ambient = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
	material.diffuse = glm::vec4(1.0f, 0.5f, 0.01f, 1.0f);
	material.specular = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
	material.shininess = 5;


	//Ids
	 //Light
	ids["LightPosition"] = glGetUniformLocation(ids["program"], "light.position");
	ids["LightAmbient"] = glGetUniformLocation(ids["program"], "light.ambient");
	ids["LightDiffuse"] = glGetUniformLocation(ids["program"], "light.diffuse");
	ids["LightSpecular"] = glGetUniformLocation(ids["program"], "light.specular");

	//Material
	ids["MaterialAmbient"] = glGetUniformLocation(ids["program"], "material.ambient");
	ids["MaterialDiffuse"] = glGetUniformLocation(ids["program"], "material.diffuse");
	ids["MaterialSpecular"] = glGetUniformLocation(ids["program"], "material.specular");
	ids["shininess"] = glGetUniformLocation(ids["program"], "material.shininess");


	ids["eye"] = glGetUniformLocation(ids["program"], "eye");
	ids["model"] = glGetUniformLocation(ids["program"], "model");



}

void Application::update()
{
	time += 0.1f;
	eye = glm::vec3( 0.0f, 3.0f, 3.0f);
	camera = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::mat4(1.0);

	light.position = glm::vec3(6.0f * cos(time), 6.0f, 6.0f * sin(time));

}

void Application::draw()
{
	//Seleccionar programa (shaders)
	glUseProgram(ids["program"]);

	//Pasar el resto de los parámetros para el programa
	glUniform1f(ids["time"], time);
	glUniformMatrix4fv(ids["camera"], 1, GL_FALSE, &camera[0][0]);
	glUniformMatrix4fv(ids["projection"], 1, GL_FALSE, &projection[0][0]);


	glUniform3fv(ids["eye"], 1, glm::value_ptr(eye));
	glUniformMatrix4fv(ids["model"], 1, GL_FALSE, glm::value_ptr(model));


	//Valores del uniform
	//uniform, ids[nombre del ID]
	glUniform3fv(ids["LightPosition"], 1, glm::value_ptr(light.position));
	glUniform4fv(ids["LightAmbient"], 1, glm::value_ptr(light.ambient));
	glUniform4fv(ids["LightDiffuse"], 1, glm::value_ptr(light.diffuse));
	glUniform4fv(ids["LightSpecular"], 1, glm::value_ptr(light.specular));


	glUniform4fv(ids["MaterialAmbient"], 1, glm::value_ptr(material.ambient));
	glUniform4fv(ids["MaterialDiffuse"], 1, glm::value_ptr(material.diffuse));
	glUniform4fv(ids["MaterialSpecular"], 1, glm::value_ptr(material.specular));
	glUniform1i(ids["Shininess"], material.shininess);



	//Seleccionar la geometria (el triangulo)
	//glBindVertexArray(ids["triangle"]);
	glBindVertexArray(oPlane.vao);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	//glDraw()
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());

}
