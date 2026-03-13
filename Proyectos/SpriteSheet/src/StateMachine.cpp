#include <iostream>
#include "StateMachine.h"
#include "ShaderFuncs.h"
#define STB_IMAGE_IMPLEMENTATION

void StateMachine::keyCallback(int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			currentState = Estados::WalkUp;
			std::cout << "Cambiando a estado: WalkUp" << std::endl;
			break;
		case GLFW_KEY_S:
			currentState = Estados::WalkDown;
			std::cout << "Cambiando a estado: WalkDown" << std::endl;
			break;
		case GLFW_KEY_D:
			currentState = Estados::WalkRight;
			std::cout << "Cambiando a estado: WalkRight" << std::endl;
			break;
		case GLFW_KEY_A:
			currentState = Estados::WalkLeft;
			std::cout << "Cambiando a estado: WalkLeft" << std::endl;
			break;
		/*case GLFW_KEY_C:
			currentState = Estados::Sit;
			std::cout << "Cambiando a estado: Sit" << std::endl;
			break;
		default:
			currentState = Estados::Idle;
			std::cout << "Cambiando a estado: Idle" << std::endl;
			break;*/
		}

	}
}

 void StateMachine::MoveAnimation(float indexX, float indexY)
{
	
	switch (currentState)
	{
	case Estados::WalkUp:
		indexX += 1.0f;
		indexY = 2.0f;
		std::cout << "IndexX" << indexX << std::endl;
		std::cout << "IndexY" << indexY << std::endl;

		break;
	case Estados::WalkDown:
		indexX += 1.0f;
		indexY = 0.0f;
		std::cout << "IndexX" << indexX << std::endl;
		std::cout << "IndexY" << indexY << std::endl;
		break;
	case Estados::WalkRight:
		indexX += 1.0f;
		indexY = 1.0f;
		std::cout << "IndexX" << indexX << std::endl;
		std::cout << "IndexY" << indexY << std::endl;
		break;
	case Estados::WalkLeft:
		indexX += 1.0f;
		indexY = 3.0f;
		std::cout << "IndexX" << indexX << std::endl;
		std::cout << "IndexY" << indexY << std::endl;
		break;
	//case Estados::Sit:
	//	// Lógica para el estado de sentado
	//	//std::cout << "El personaje está sentado." << std::endl;
	//	break;
	//case Estados::Idle:
	//	// Lógica para el estado de inactividad
	//	//std::cout << "El personaje está en estado Idle." << std::endl;
	//	break;
	}
	std::cout << "StateMachine" << std::endl;
	//if (indexX > tile.x - 1.0) //Si el indexX o indexY se pasan de los límites, se regresa a 0 
	//{
	//	indexX = 0.0f;
	//}
	//if (indexY > tile.y - 1.0)
	//{
	//	indexY = 0.0f;
	//}

	//for (int i = 0; i < 3; i++) //Filas X
	//{

	//	for (int j = 0; j < 3; j++) //Columnas Y
	//	{

	//	}
	//}
}



//Variables
//limites de indexX e indexY 


//En funciones
//Si presiono D, se aumenta el indexX y se checa que no se pase, si lo pasa se regresa a 0, 
//si presiono A, se disminuye el indexX y se checa que no se pase, si lo pasa se regresa al maximo, 
//si presiono S, se aumenta el indexY y se checa que no se pase, si lo pasa se regresa a 0, 
//si presiono W, se disminuye el indexY y se checa que no se pase, si lo pasa se regresa al maximo.

//Si lo dejo unos segundos sin tocar inicia el estado de sentado, si vuelven a pasar otros segundos sin tocar, inicia el estado de idle, si presiono cualquier tecla, se regresa al estado de caminando.

//En caso de que presione A o D, el indice mínimo siempre va a ser 0 y el máximo va a ser el tiles.x
//En caso de que presione W o S, el indice mínimo siempre va a ser 0 y el máximo va a ser el tiles.y
