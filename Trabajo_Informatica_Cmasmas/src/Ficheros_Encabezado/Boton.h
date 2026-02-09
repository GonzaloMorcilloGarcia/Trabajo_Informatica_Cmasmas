#pragma once

//INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias de OpenGL //

#include <freeglut.h>

// Otras Librerias //

#include <algorithm> // Para std::min y std::max //
#include <cmath> // Para std::lround //      

// Ficheros de Encabezado //

#include "funciones_globales.h"
#include "Color.h"
#include "Vector_2D.h"

#include "Rectangulo.h"

class Boton
{
	Rectangulo interior_boton {};
	Rectangulo borde_boton{};

	int ancho_boton {}, alto_boton {}, ancho_borde {};

public:

	Boton();

	Boton (Vector_2D centro, float ancho, float alto, Color color_interior, Color color_borde, int ancho_borde);

	void dibujar_Boton();

	bool Contiene_Coordenadas(Vector_2D coordenada);
};

