#pragma once

//INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias de OpenGL //

#include <freeglut.h>

// Otras Librerias //
      
// Ficheros de Encabezado //

#include "funciones_globales.h"
#include "Color.h"
#include "Vector_2D.h"

class Rectangulo
{
	public:


	Rectangulo();

	Rectangulo (Vector_2D centro, int ancho, int alto, Color color);

	void dibujar_Rectangulo();

private:

	Vector_2D centro_rectangulo {};

	int ancho_rectangulo {}, alto_rectangulo {};

	Color color_rectangulo {};

	friend class Boton; // Declaramos a la clase Boton como amiga para que pueda acceder a los miembros privados de Rectangulo //
};

