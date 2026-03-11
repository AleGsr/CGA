
#pragma once
#include <iostream>
#include "glad/glad.h"
#include <string>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum class Estados {
	WalkUp,
	WalkDown,
	WalkRight,
	WalkLeft,
	Sit,
	Idle
};

class StateMachine
{
	
private:
	Estados currentState{ Estados::Idle };
	float maxIndexX{ 0.0f };
	float maxIndexY{ 0.0f };


public:
	GLFWwindow* window;

	//teclas
	void keyCallback(int key, int scancode, int action, int mods);

	//maquina de estados
	void MoveAnimation(float indexX, float indexY);
};
