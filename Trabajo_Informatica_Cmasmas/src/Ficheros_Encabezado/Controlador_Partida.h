#pragma once

//INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias de OpenGL //
#include <freeglut.h>

// Otras Librerias //

#include <algorithm> // Para std::min y std::max //
#include <cmath> // Para std::lround //      
#include <iostream> // Para std::cout y std::endl //
#include "ETSIDI.h"

// Ficheros de Encabezado //

#include "funciones_globales.h"
#include "Vector_2D.h"

#include "Boton.h"

class Controlador_Partida
{
	enum class Estados_Partida
	{
		// Estados Principales del Juego //

		PANTALLA_TABLERO,
		PANTALLA_BATALLA,

		// Estados de Victoria o Derrota //

		PANTALLA_WIN,
		PANTALLA_GAME_OVER,
	};

public:

	void iniciar_Controlador();

	void cambiar_Estado(Estados_Partida estado_siguiente);

	void iniciar_Estado();

	void dibujar_Estado();

	void teclas_Partida(unsigned char key);
	void actualizar_Estado(unsigned char key);

	void mouse_Partida(Vector_2D coordenadas_mouse, bool leftClick);
	void actualizar_Estado(Vector_2D coordenadas_mouse, bool leftClick);

	void actualizar_Hover(Vector_2D coordenadas_mouse);

	void loop_Juego(int value);

	Estados_Partida get_Estado_Actual() const { return Estado_Actual; }

private:

	Estados_Partida Estado_Actual, Estado_Anterior;

	Boton Boton_Jugar{}, Boton_Ajustes{}, Boton_Salir{}, Boton_Musica{}, Boton_Anterior{}, Boton_Pausa{}, Boton_Siguiente{};

	Boton Boton_Menu_Principal{}, Boton_Creditos{}, Boton_Volumen{}, Boton_Bajar_Volumen{}, Boton_Subir_Volumen{};

	GLuint Fondo_Pantalla_Batalla = 0;
	GLuint Fondo_Pantalla_Win = 0;
	GLuint Fondo_Pantalla_Game_Over = 0;
};

