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

void Application::setupProgram()
{
	std::string vertexShader = loadTextFile("shaders/VertexTexture.glsl");
	std::string fragmentShader = loadTextFile("shaders/FragmentTexture.glsl");
	ids["program"] = InitializeProgram(vertexShader, fragmentShader);
	//ids["time2"] = glGetUniformLocation(ids["program"], "time");
	ids["model"] = glGetUniformLocation(ids["program"], "model");
	ids["camera"] = glGetUniformLocation(ids["program"], "camera");
	ids["height"] = glGetUniformLocation(ids["program"], "height"); 
	ids["projection"] = glGetUniformLocation(ids["program"], "projection");
	ids["texture0"] = glGetUniformLocation(ids["program"], "texture0");
	ids["texture1"] = glGetUniformLocation(ids["program"], "texture1");
	//ids["mixerV"] = glGetUniformLocation(ids["program"], "mixerV");
}

GLuint Application::setupTexture(const std::string& path)
{
	int width, height, channels;
	unsigned char* img = stbi_load(path.c_str(), //carga la img a un arreglo, investiga cuanto mide y cuantos canales maneja
		&width, &height, &channels, 4);

	if (img == nullptr)
	{
		std::cout << "No se pudo cargar textura: " << path << std::endl;
		return 0;
	}


	GLuint texID = -1; //Se inicializa
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

	stbi_image_free(img);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
	
	//return GLuint();
}



void Application::keyCallback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
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
	zoom *= (1.0f + (float)yoffset * sensibilidad * 0.1f); //Se modifica la escala segun el scroll :)

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
	setupGeometry();
	setupProgram();
	ids["Diffuse"] = setupTexture("Textures/RuggedTerrainDiffuse.png");
	ids["HeightMap"] = setupTexture("Textures/RuggedTerrainHeightMap.png");
}

void Application::update()
{
	time += 0.01f;

	eye = glm::vec3( 0.0f, 3.0f , 5.0f);
	center = glm::vec3(0.01f, 0.01f, 0.01f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	camera = glm::lookAt(eye, center, up);

	model = glm::mat4(1.0f);

	model = glm::rotate(model, glm::radians(moveHorizontal), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(moveVertical), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(zoom, zoom, zoom));


	projection = glm::perspective(glm::radians(45.0f), (1024.0f / 768.0f), 0.1f, 200.0f);
}

void Application::draw()
{
	//Seleccionar programa (shaders)
	glUseProgram(ids["program"]);

	//Pasar el resto de los parámetros para el programa
	//glUniform1f(ids["time2"], time);
	glUniformMatrix4fv(ids["model"], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(ids["camera"],1 , GL_FALSE, &camera[0][0]);
	glUniformMatrix4fv(ids["projection"], 1, GL_FALSE, &projection[0][0]);
	glUniform1f(ids["height"], 0.5f);
	
	//Seleccionar la geometria (el triangulo)
	//glBindVertexArray(ids["triangle"]);
	glBindVertexArray(oPlane.vao);


	glUniform1f(ids["mixerV"], mixerV);

	//Seleccionar las texturas


	//texture0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ids["Diffuse"]);
	glUniform1i(ids["texture0"], 0);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);


	//texture1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ids["HeightMap"]);
	glUniform1i(ids["texture1"], 1);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);





	//glDraw()
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());



}
