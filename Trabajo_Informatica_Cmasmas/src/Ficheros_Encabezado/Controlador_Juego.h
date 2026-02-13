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
#include "Controlador_Audio.h"
#include "Controlador_Partida.h"
#include "Vector_2D.h"

#include "Boton.h"

class Controlador_Juego
{
	enum class Estados_Juego
	{
		// Estados Principales del Juego //

		PANTALLA_TITULO,
		PANTALLA_MENU,
		PANTALLA_PARTIDA,
	
		// Estados de Ajustes y Creditos //

		PANTALLA_AJUSTES,
		PANTALLA_CREDITOS
	};

public:

	void iniciar_Controlador();

	void cambiar_Estado(Estados_Juego estado_siguiente);

	void iniciar_Estado();

	void dibujar_Estado();

	void actualizar_Estado(unsigned char key);

	void actualizar_Estado(Vector_2D coordenadas_mouse, bool leftClick);

	void actualizar_Hover(Vector_2D coordenadas_mouse);

	void loop_Juego(int value);

	Estados_Juego get_Estado_Actual() const { return Estado_Actual; }

private:

	Estados_Juego Estado_Actual, Estado_Anterior;	

	Boton Boton_Jugar{}, Boton_Ajustes{}, Boton_Salir{}, Boton_Musica{}, Boton_Anterior{}, Boton_Pausa{}, Boton_Siguiente{};

	Boton Boton_Menu_Principal{}, Boton_Creditos{}, Boton_Volumen{}, Boton_Bajar_Volumen{}, Boton_Subir_Volumen{};

	GLuint Fondo_Pantalla_Titulo = 0;
	GLuint Fondo_Pantalla_Menu = 0;
	GLuint Fondo_Pantalla_Partida = 0;

	Controlador_Audio controlador_audio;
	Controlador_Partida controlador_partida;


};

