#include "Controlador_Partida.h"


void Controlador_Partida::iniciar_Controlador()
{
	Estado_Actual = Estados_Partida::PANTALLA_TABLERO;

	iniciar_Estado();
}

void Controlador_Partida::cambiar_Estado(Estados_Partida estado_siguiente)
{
	Estado_Anterior = Estado_Actual;
	Estado_Actual = estado_siguiente;

	iniciar_Estado();

	std::cout << "Estado de Controlador de Partida Actualizado \n";
}

void Controlador_Partida::iniciar_Estado()
{
	switch (Estado_Actual)
	{
	case Estados_Partida::PANTALLA_TABLERO:
	{
		break;
	}

	case Estados_Partida::PANTALLA_BATALLA:
	{
		
		break;
	}

	case Estados_Partida::PANTALLA_PAUSA:
	{

		break;
	}

	case Estados_Partida::PANTALLA_WIN:
	{
		break;
	}

	case Estados_Partida::PANTALLA_GAME_OVER:
	{
		break;
	}

	default:
	{
		std::cout << "Error: Estado no reconocido en Controlador_Partida.cpp/iniciar_Estado() \n";

		exit(1);

		break;
	}

	}
}

void Controlador_Partida::dibujar_Estado()
{
	switch (Estado_Actual)
	{
	case Estados_Partida::PANTALLA_TABLERO:
	{
		//dibujar_Fondo();

		break;
	}

	case Estados_Partida::PANTALLA_BATALLA:
	{
		//dibujar_Fondo();

		break;

	}

	case Estados_Partida::PANTALLA_PAUSA:
	{
		//dibujar_Fondo();

		break;
	}

	case Estados_Partida::PANTALLA_WIN:
	{
		//dibujar_Fondo();

		break;
	}

	case Estados_Partida::PANTALLA_GAME_OVER:
	{
		//dibujar_Fondo();

		break;
	}

	default:
	{
		std::cout << "Error: Estado no reconocido en Controlador_Partida.cpp/dibujar_Estado() \n";

		exit(1);

		break;
	}
	}
}

void Controlador_Partida::teclas_Partida(unsigned char key)
{
	actualizar_Estado(key);
}

void Controlador_Partida::actualizar_Estado(unsigned char key)
{
	if (Estado_Actual == Estados_Partida::PANTALLA_TABLERO)
	{
		if (key == 27) // Escape
		{
			cambiar_Estado(Estados_Partida::PANTALLA_PAUSA);
		}
	}

	else if (Estado_Actual == Estados_Partida::PANTALLA_BATALLA)
	{
		if (key == 27) // Escape
		{
			cambiar_Estado(Estados_Partida::PANTALLA_PAUSA);
		}
	}

	else if (Estado_Actual == Estados_Partida::PANTALLA_PAUSA)
	{
	}

	else if (Estado_Actual == Estados_Partida::PANTALLA_WIN)
	{

	}

	else if (Estado_Actual == Estados_Partida::PANTALLA_GAME_OVER)
	{

	}
}

void Controlador_Partida::mouse_Partida(Vector_2D coordenadas_mouse, bool leftClick)
{
	actualizar_Estado(coordenadas_mouse, leftClick);
}

void Controlador_Partida::actualizar_Estado(Vector_2D coordenadas_mouse, bool leftClick)
{
	// 1) En la pantalla de título: cualquier click (izq/der) vale para pasar al menú
	if (Estado_Actual == Estados_Partida::PANTALLA_TABLERO)
	{
		cambiar_Estado(Estados_Partida::PANTALLA_BATALLA);
		return;
	}

	// 2) Para interactuar con botones, exigimos click izquierdo
	if (!leftClick) return;

	// 3) Menú principal
	if (Estado_Actual == Estados_Partida::PANTALLA_PAUSA)
	{
		return;
	}

	// 4) Ajustes
	if (Estado_Actual == Estados_Partida::PANTALLA_WIN)
	{
		return;
	}

	if (Estado_Actual == Estados_Partida::PANTALLA_GAME_OVER)
	{
		return;
	}

}

void Controlador_Partida::actualizar_Hover(Vector_2D coordenadas_mouse)
{
	if (Estado_Actual == Estados_Partida::PANTALLA_TABLERO)
	{
		
	}

	if (Estado_Actual == Estados_Partida::PANTALLA_BATALLA)
	{
		
	}

	if (Estado_Actual == Estados_Partida::PANTALLA_PAUSA)
	{
		
	}
}

void Controlador_Partida::loop_Juego(int value)
{

}
