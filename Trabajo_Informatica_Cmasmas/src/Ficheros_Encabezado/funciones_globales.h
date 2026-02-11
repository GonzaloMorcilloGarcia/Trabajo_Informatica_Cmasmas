#pragma once

//INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias de OpenGL //

#include <freeglut.h>

// Otras Librerias //

#include <string>
#include "ETSIDI.h"

// Ficheros de Encabezado //

#include "Vector_2D.h"

// PARAMETROS GLOBALES //

constexpr int VIRTUAL_W = 1920;
constexpr int VIRTUAL_H = 1080;

constexpr int FPS = 60;
constexpr int FRAME_MS = 1000 / FPS;

// FUNCIONES GLOBALES //

// Función auxiliar para verificar si una coordenada está dentro de un área rectangular definida por sus límites (x, y, ancho, alto) //

inline bool Contiene(Vector_2D coordenada, int limite_x, int limite_y, int limite_w, int limite_h)
{
    return (coordenada.x >= limite_x && coordenada.x < limite_x + limite_w && coordenada.y >= limite_y && coordenada.y < limite_y + limite_h);
}

// Función auxiliar para dibujar texto usando una fuente bitmap //

inline void escribe_BitmapText(const std::string& text, float x, float y, void* fuente)
{
    glRasterPos2f(x, y);

    for (unsigned char c : text)
    {
        glutBitmapCharacter(fuente, c);
    }
}

// Función auxiliar para calcular el ancho del texto usando una fuente bitmap //

inline int calcular_Ancho_Texto(const std::string& texto, void* fuente)
{
    int ancho_Total = 0;
    for (unsigned char c : texto)
    {
        ancho_Total += glutBitmapWidth(fuente, c);
    }
    return ancho_Total;
}

void dibujar_Fondo(GLuint texId);