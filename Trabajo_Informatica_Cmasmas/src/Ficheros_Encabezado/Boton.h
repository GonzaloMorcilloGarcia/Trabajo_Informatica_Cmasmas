#pragma once

//INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias de OpenGL //

#include <freeglut.h>

// Otras Librerias //

#include <algorithm> // Para std::min y std::max //
#include <cmath> // Para std::lround //      
#include <string>
#include "ETSIDI.h"

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

	Color color_predeterminado_boton{};

	std::string texto_boton{};

	bool resaltado_boton{};
	

public:

	Boton();

	Boton (Vector_2D centro, float ancho, float alto, Color color_predeterminado, int ancho_borde, std::string texto);

	void dibujar_Boton();

	void actualizar_Hover(Vector_2D coordenada_mouse);

	bool Contiene_Coordenadas(Vector_2D coordenada);

	inline void set_Texto(const std::string& nuevo_texto)
	{
		texto_boton = nuevo_texto;
	}

};

