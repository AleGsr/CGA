#include "Application.h"
#include <iostream>
#include "ShaderFuncs.h"
#include "glm/gtc/type_ptr.hpp"


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

void Application::setupProgramGouraud()
{
	std::string vertexShader = loadTextFile("shaders/VertexADS.glsl");
	std::string fragmentShader = loadTextFile("shaders/FragmentADS.glsl");
	ids["programGouraud"] = InitializeProgram(vertexShader, fragmentShader);
	ids["time"] = glGetUniformLocation(ids["programGouraud"], "time");
	ids["camera"] = glGetUniformLocation(ids["programGouraud"], "camera");
	ids["model"] = glGetUniformLocation(ids["programGouraud"], "model");
	ids["projection"] = glGetUniformLocation(ids["programGouraud"], "projection");
}

void Application::setupProgramPhong()
{
	std::string vertexShader = loadTextFile("shaders/VertexPhong.glsl");
	std::string fragmentShader = loadTextFile("shaders/FragmentPhong.glsl");
	ids["programPhong"] = InitializeProgram(vertexShader, fragmentShader);
	ids["time"] = glGetUniformLocation(ids["programPhong"], "time");
	ids["camera"] = glGetUniformLocation(ids["programPhong"], "camera");
	ids["model"] = glGetUniformLocation(ids["programPhong"], "model");
	ids["projection"] = glGetUniformLocation(ids["programPhong"], "projection");
}

void Application::keyCallback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		currentProgram = 0;
		std::cout << "Programa Gouraud cargado" << std::endl;
	}
	else if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		currentProgram = 1;
		std::cout << "Programa Phong cargado" << std::endl;
	}

}

void Application::mouseCallback(double xpos, double ypos)
{
	glfwGetCursorPos(window, &xpos, &ypos);

	//Calculo el centro de la ventana para el mouse
	float centerMouseX = WINDOW_WIDTH / 2.0f;
	float centerMouseY = WINDOW_HEIGHT / 2.0f;

	moveHorizontal = (xpos - centerMouseX) * 0.15;
	moveVertical = (ypos - centerMouseY) * 0.15;


}

void Application::ScrollCallback(double xoffset, double yoffset)
{
	const float sensibilidad = 0.30f;
	zoom *= (1.0f + (float)yoffset * sensibilidad * 0.1f); 

	if (zoom < minScale)
	{
		zoom = minScale;
	}
	if (zoom > maxScale)
	{
		zoom = maxScale;
	}

}

void Application::setup()
{
	std::cout << "Presiona 'G' para Gouraud" << std::endl;
	std::cout << "Presiona 'P' para Phong" << std::endl;

	setupGeometry();
	setupProgramGouraud();
	setupProgramPhong();
	

	projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 100.0f);

	light.position = glm::vec3(1.0f, 0.5f, 0.01f);
	light.ambient = glm::vec4(0.01f, 1.2f, 0.01f, 1.0f);
	light.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	light.specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	material.ambient = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
	material.diffuse = glm::vec4(1.0f, 0.5f, 0.01f, 1.0f);
	material.specular = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
	material.shininess = 5;


	//Goureaud
	 //Light
	ids["LightPosition"] = glGetUniformLocation(ids["programGouraud"], "light.position");
	ids["LightAmbient"] = glGetUniformLocation(ids["programGouraud"], "light.ambient");
	ids["LightDiffuse"] = glGetUniformLocation(ids["programGouraud"], "light.diffuse");
	ids["LightSpecular"] = glGetUniformLocation(ids["programGouraud"], "light.specular");

	//Material
	ids["MaterialAmbient"] = glGetUniformLocation(ids["programGouraud"], "material.ambient");
	ids["MaterialDiffuse"] = glGetUniformLocation(ids["programGouraud"], "material.diffuse");
	ids["MaterialSpecular"] = glGetUniformLocation(ids["programGouraud"], "material.specular");
	ids["shininess"] = glGetUniformLocation(ids["programGouraud"], "material.shininess");


	ids["eye"] = glGetUniformLocation(ids["programGouraud"], "eye");
	ids["model"] = glGetUniformLocation(ids["programGouraud"], "model");


	//Phong
	 //Light
	ids["LightPosition"] = glGetUniformLocation(ids["programPhong"], "light.position");
	ids["LightAmbient"] = glGetUniformLocation(ids["programPhong"], "light.ambient");
	ids["LightDiffuse"] = glGetUniformLocation(ids["programPhong"], "light.diffuse");
	ids["LightSpecular"] = glGetUniformLocation(ids["programPhong"], "light.specular");

	//Material
	ids["MaterialAmbient"] = glGetUniformLocation(ids["programPhong"], "material.ambient");
	ids["MaterialDiffuse"] = glGetUniformLocation(ids["programPhong"], "material.diffuse");
	ids["MaterialSpecular"] = glGetUniformLocation(ids["programPhong"], "material.specular");
	ids["shininess"] = glGetUniformLocation(ids["programPhong"], "material.shininess");


	ids["eye"] = glGetUniformLocation(ids["programPhong"], "eye");
	ids["model"] = glGetUniformLocation(ids["programPhong"], "model");


}

void Application::update()
{
	time += 0.1f;
	eye = glm::vec3(0.0f, 3.0f, 5.0f);
	center = glm::vec3(0.01f, 0.01f, 0.01f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	camera = glm::lookAt(eye, center, up);
	model = glm::mat4(1.0);

	light.position = glm::vec3(6.0f * cos(time), 6.0f, 6.0f * sin(time));

	model = glm::mat4(1.0f);

	model = glm::rotate(model, glm::radians(moveHorizontal), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(moveVertical), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(zoom, zoom, zoom));


	projection = glm::perspective(glm::radians(45.0f), (1024.0f / 768.0f), 0.1f, 200.0f);

}

void Application::draw()
{
	//Seleccionar programa (shaders)

	GLuint program;

	if (currentProgram == 0)
	{
		program = ids["programGouraud"];
	}
	else if (currentProgram == 1)
	{
		program = ids["programPhong"];
	}

	glUseProgram(program);


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
	glUniform1i(ids["shininess"], material.shininess);



	//Seleccionar la geometria (el triangulo)
	//glBindVertexArray(ids["triangle"]);
	glBindVertexArray(oPlane.vao);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	//glDraw()
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());

	
}
