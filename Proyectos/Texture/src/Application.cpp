#include "Application.h"
#include <iostream>
#include "ShaderFuncs.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Application::Application() : oPlane()
{

}


void Application::setupGeometry()
{
	oPlane.createPlane(2);

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
	std::string vertexShader = loadTextFile("shaders/VertexCamera.glsl");
	std::string fragmentShader = loadTextFile("shaders/FragmentCamera.glsl");
	ids["program2"] = InitializeProgram(vertexShader, fragmentShader);
	ids["time2"] = glGetUniformLocation(ids["program2"], "time");
	ids["camera"] = glGetUniformLocation(ids["program2"], "camera");
	ids["projection"] = glGetUniformLocation(ids["program2"], "projection");
}

GLuint Application::setupTexture(const std::string& path)
{
	int width, height, channels;
	unsigned char* img = stbi_load(path.c_str(), //carga la img a un arreglo, investiga cuanto mide y cuantos canales maneja
		&width, &height, &channels, 4);

	if (img == nullptr)
		return -1;


	GLuint textID = -1; //Se inicializa
	glGenTextures(1, &textID);
	glBindTexture(GL_TEXTURE_2D, textID);
	


	//return GLuint();
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
	ids["gato"] = setupTexture("Textures/Gato.png");
	projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 100.0f);
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
	
	//Seleccionar la geometria (el triangulo)
	//glBindVertexArray(ids["triangle"]);
	glBindVertexArray(oPlane.vao);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glDraw()
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());
}
