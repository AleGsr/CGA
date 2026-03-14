#include <iostream>
#include "StateMachine.h"
#include "ShaderFuncs.h"
#include <chrono>
std::chrono::steady_clock::time_point lastKeyTime = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point lastFrameTime = std::chrono::steady_clock::now();
#define STB_IMAGE_IMPLEMENTATION

void StateMachine::keyCallback(int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE) 
	{
		if (key == GLFW_KEY_W || key == GLFW_KEY_S ||
			key == GLFW_KEY_D || key == GLFW_KEY_A || key == GLFW_KEY_C)
		{
			currentState = Estados::Waiting;
		}
	}

	if (action == GLFW_PRESS)
	{
		lastKeyTime = std::chrono::steady_clock::now();
		sitPlayed = false;

		switch (key)
		{
		case GLFW_KEY_W:
			currentState = Estados::WalkUp;
			break;
		case GLFW_KEY_S:
			currentState = Estados::WalkDown;
			break;
		case GLFW_KEY_D:
			currentState = Estados::WalkRight;
			break;
		case GLFW_KEY_A:
			currentState = Estados::WalkLeft;
			break;
		case GLFW_KEY_C:
			currentState = Estados::Sit;
			break;
		}
	}
}

 void StateMachine::MoveAnimation(float& indexX, float& indexY, glm::vec2 tiles)
{
	 auto now = std::chrono::steady_clock::now();
	 auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFrameTime).count();

	 if (elapsed > 120)
	 {
		 if (currentState != Estados::Waiting)
		 {
			 indexX += 1.0f;
		 }

		 lastFrameTime = now;
	 }

	//Aquí se calcula el tiempo
	switch (currentState)
	{
	case Estados::WalkUp:
		indexY = 2.0f;
		break;
	case Estados::WalkDown:
		indexY = 0.0f;
		break;
	case Estados::WalkRight:
		indexY = 1.0f;
		break;
	case Estados::WalkLeft:
		indexY = 3.0f;
		break;
	case Estados::Sit:
		indexY = 4.0f;

		if (indexX > tiles.x - 1.0f)
		{
			indexX = 0.0f;
			sitPlayed = true;
			currentState = Estados::Idle;
		}
		break;
	case Estados::Idle:
		indexY = 5.0f;
		break;
	case Estados::Waiting:
		CheckLastMovement();
		break;
	}

	if (indexX > tiles.x - 1.0) //Si el indexX o indexY se pasan de los límites, se regresa a 0 
	{
		indexX = 0.0f;
	}
	if (indexY > tiles.y - 1.0)
	{
		indexY = 0.0f;
	}

}

 void StateMachine::CheckLastMovement()
 {
	 auto now = std::chrono::steady_clock::now();
	 auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastKeyTime).count();

	 if (elapsed > 2000 && !sitPlayed)
	 {
		 currentState = Estados::Sit;
	 }
 }
