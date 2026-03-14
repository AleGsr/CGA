#include <iostream>
#include "StateMachine.h"
#include "ShaderFuncs.h"
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
	//Aquí se calcula el tiempo
	switch (currentState)
	{
	case Estados::WalkUp:
		//Se checa el tiempo
		indexX += 1.0f;
		indexY = 2.0f;
		break;
	case Estados::WalkDown:
		indexX += 1.0f;
		indexY = 0.0f;
		break;
	case Estados::WalkRight:
		indexX += 1.0f;
		indexY = 1.0f;
		break;
	case Estados::WalkLeft:
		indexX += 1.0f;
		indexY = 3.0f;
		break;
	//case Estados::Sit:
	//	indexX += 1.0f;
	//	indexY = 4.0f;
	//	if (indexX > tiles.x)
	//	{
	//		currentState = Estados::Idle;
	//	}
	//	break;
	//case Estados::Idle:
	//	indexX += 1.0f;
	//	indexY = 5.0f;
	//	break;
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
	 //Chrono checa el tiempo que lleva sin presionar una tecla
	 //Si el tiempo es mayor a 2s, 2000ms entonces current state es sit
	 //Bool en sit es true
	 //Se calcula el tiempo que lleva en sit
	 //Cuando acabe la animación de sit empieza la de idle

 }
