#include "Boton.h"

Boton::Boton()
{
	interior_boton = Rectangulo(); // Inicializamos el interior del botón con el constructor por defecto de Rectangulo //

	borde_boton = Rectangulo(); // Inicializamos el borde del botón con el constructor por defecto de Rectangulo //
}

Boton::Boton(Vector_2D centro, float ancho, float alto, Color color_interior, Color color_borde, int ancho_borde)
{
	interior_boton.centro_rectangulo = borde_boton.centro_rectangulo = centro; // Asignamos las coordenadas del centro del botón //

	interior_boton.ancho_rectangulo = ancho; // Asignamos el ancho del interior del botón a partir del valor proporcionado //
	interior_boton.alto_rectangulo = alto; // Asignamos el alto del interior del botón a partir del valor proporcionado //
	interior_boton.color_rectangulo = color_interior; // Asignamos el color del interior del botón a partir del valor proporcionado //

	borde_boton.ancho_rectangulo = ancho + 2 * ancho_borde; // El ancho del borde es el ancho del interior más el doble del ancho del borde //
	borde_boton.alto_rectangulo = alto + 2 * ancho_borde; // El alto del borde es el alto del interior más el doble del ancho del borde //
	borde_boton.color_rectangulo = color_borde; // Asignamos el color del borde del botón a partir del valor proporcionado //
}

void Boton::dibujar_Boton()
{
	borde_boton.dibujar_Rectangulo(); // Dibujamos el borde del botón //

	interior_boton.dibujar_Rectangulo(); // Dibujamos el interior del botón //
}

bool Boton::Contiene_Coordenadas( Vector_2D coordenada)
{
    // Esquina Inferior Izquierda del Rectángulo // 

    const int x_min = static_cast<int> (interior_boton.centro_rectangulo.x - interior_boton.ancho_rectangulo * 0.5f);

    const int y_min = static_cast<int>(interior_boton.centro_rectangulo.y - interior_boton.alto_rectangulo * 0.5f);

    return Contiene(coordenada,x_min,y_min, static_cast<int>(interior_boton.ancho_rectangulo), static_cast<int>(interior_boton.alto_rectangulo));
}