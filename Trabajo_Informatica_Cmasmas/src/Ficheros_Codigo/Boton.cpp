#include "Boton.h"

Boton::Boton()
{
	interior_boton = Rectangulo(); // Inicializamos el interior del botón con el constructor por defecto de Rectangulo //

	borde_boton = Rectangulo(); // Inicializamos el borde del botón con el constructor por defecto de Rectangulo //
}

Boton::Boton(Vector_2D centro, float ancho, float alto, Color color_predeterminado, int borde, std::string texto)
{
	ancho_boton = ancho; // Guardamos el ancho del botón para poder restaurarlo después de resaltar //
	alto_boton = alto; // Guardamos el alto del botón para poder restaurarlo después de resaltar //
	ancho_borde = borde; // Guardamos el ancho del borde para poder restaurarlo después de resaltar //

	interior_boton.centro_rectangulo = borde_boton.centro_rectangulo = centro; // Asignamos las coordenadas del centro del botón //

	interior_boton.ancho_rectangulo = ancho; // Asignamos el ancho del interior del botón a partir del valor proporcionado //
	interior_boton.alto_rectangulo = alto; // Asignamos el alto del interior del botón a partir del valor proporcionado //
	interior_boton.color_rectangulo = color_predeterminado; // Asignamos el color del interior del botón a partir del valor proporcionado //

	borde_boton.ancho_rectangulo = ancho + 2 * borde; // El ancho del borde es el ancho del interior más el doble del ancho del borde //
	borde_boton.alto_rectangulo = alto + 2 * borde; // El alto del borde es el alto del interior más el doble del ancho del borde //
	borde_boton.color_rectangulo = {0,0,0}; // Asignamos el color del borde del botón a partir del valor proporcionado //

	texto_boton = texto; // Asignamos el texto del botón a partir del valor proporcionado //

	color_predeterminado_boton = color_predeterminado; // Guardamos el color predeterminado del botón para poder restaurarlo después de resaltar //
}

void Boton::dibujar_Boton()
{
	borde_boton.dibujar_Rectangulo(); // Dibujamos el borde del botón //

	interior_boton.dibujar_Rectangulo(); // Dibujamos el interior del botón //

    // Fuente
    void* fuente = GLUT_BITMAP_HELVETICA_18;

    // Color del texto (negro)
    glColor3ub(0, 0, 0);

    // Ancho del texto para centrar
    const int wTexto = calcular_Ancho_Texto(texto_boton, fuente);

    // Coordenadas centradas (x: centrado real; y: ajuste visual)
    const float xTexto = interior_boton.centro_rectangulo.x - wTexto * 0.5f;
    const float yTexto = interior_boton.centro_rectangulo.y - 9.0f; // ajuste típico para Helvetica 18

    escribe_BitmapText(texto_boton, xTexto, yTexto, fuente);

}

void Boton::actualizar_Hover (Vector_2D mouse)
{
    resaltado_boton = Contiene_Coordenadas(mouse);

    if (resaltado_boton)
    {
        // Color hover
        interior_boton.color_rectangulo = Color(255, 255, 0);

        // Escala suave (10%)
        interior_boton.ancho_rectangulo = (int)(ancho_boton * 1.1f);
        interior_boton.alto_rectangulo = (int)(alto_boton * 1.1f);

        borde_boton.ancho_rectangulo =
            interior_boton.ancho_rectangulo + 2 * ancho_borde;
        borde_boton.alto_rectangulo =
            interior_boton.alto_rectangulo + 2 * ancho_borde;
    }
    else
    {
        // Vuelve al estado normal
        interior_boton.color_rectangulo = color_predeterminado_boton;

        interior_boton.ancho_rectangulo = ancho_boton;
        interior_boton.alto_rectangulo = alto_boton;

        borde_boton.ancho_rectangulo = ancho_boton + 2 * ancho_borde;
        borde_boton.alto_rectangulo = alto_boton + 2 * ancho_borde;
    }
}

bool Boton::Contiene_Coordenadas( Vector_2D coordenada)
{
    // Esquina Inferior Izquierda del Rectángulo // 

    const int x_min = static_cast<int> (interior_boton.centro_rectangulo.x - interior_boton.ancho_rectangulo * 0.5f);

    const int y_min = static_cast<int>(interior_boton.centro_rectangulo.y - interior_boton.alto_rectangulo * 0.5f);

    return Contiene(coordenada,x_min,y_min, static_cast<int>(interior_boton.ancho_rectangulo), static_cast<int>(interior_boton.alto_rectangulo));
}

void Boton::Resaltar_Boton(Vector_2D coordenada)
{
	if (Contiene_Coordenadas(coordenada))
	{
		interior_boton.color_rectangulo = Color(255, 255, 0); // Cambia el color del interior del botón a amarillo para resaltar //
	}
	else
	{
		interior_boton.color_rectangulo = color_predeterminado_boton; // Si el mouse no está sobre el botón, vuelve al color original (rojo) //
	}
}