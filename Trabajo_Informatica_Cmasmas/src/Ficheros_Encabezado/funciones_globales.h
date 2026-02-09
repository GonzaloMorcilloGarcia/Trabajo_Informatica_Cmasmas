#pragma once

//INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias de OpenGL //

#include <freeglut.h>

// Otras Librerias //

// Ficheros de Encabezado //

#include "Vector_2D.h"


inline bool Contiene(Vector_2D coordenada, int limite_x, int limite_y, int limite_w, int limite_h)
{
    return (coordenada.x >= limite_x && coordenada.x < limite_x + limite_w && coordenada.y >= limite_y && coordenada.y < limite_y + limite_h);
}
