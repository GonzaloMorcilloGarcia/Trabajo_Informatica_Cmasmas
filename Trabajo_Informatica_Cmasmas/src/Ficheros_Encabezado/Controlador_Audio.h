#pragma once

//INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias de OpenGL //
#include <freeglut.h>

// Otras Librerias //

#include <algorithm> // Para std::min y std::max //
#include <cmath> // Para std::lround //      
#include <iostream> // Para std::cout y std::endl //
#include <vector>
#include "ETSIDI.h"
#include <SFML/Audio.hpp>

// Ficheros de Encabezado //

#include "funciones_globales.h"
#include "Boton.h"
#include "Controlador_Juego.h"

struct Cancion 
{
	std::string nombre_cancion;
	std::string ruta_cancion;

	int duracion_cancion; // Duracion en segundos
	int id_cancion; // Identificador unico para cada cancion

};

class Controlador_Audio
{
	std::vector <Cancion> lista_canciones;

	public:

	void iniciar_Controlador_Audio();

	void reproducir_Cancion(const std::string& ruta_cancion);

	void detener_Cancion();

	void reiniciar_Cancion();
};

