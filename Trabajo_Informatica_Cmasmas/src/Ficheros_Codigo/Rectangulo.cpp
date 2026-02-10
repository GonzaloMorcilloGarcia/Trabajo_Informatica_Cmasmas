#include "Rectangulo.h"

Rectangulo::Rectangulo()
{
	centro_rectangulo = { 0, 0 }; // Inicializamos el centro del rectángulo en el origen (0,0) //
	ancho_rectangulo = 5; // Inicializamos el ancho del rectángulo a 0 //
	alto_rectangulo = 5; // Inicializamos el alto del rectángulo a 0 //
	color_rectangulo = { 0, 0, 0}; // Inicializamos el color del rect
};

Rectangulo::Rectangulo (Vector_2D centro, int ancho, int alto, Color color)
{
	centro_rectangulo = centro; // Asignamos las coordenadas del centro del rectángulo a partir del vector proporcionado //
	
	ancho_rectangulo = ancho; // Asignamos el ancho del rectángulo a partir del valor proporcionado //
	alto_rectangulo = alto; // Asignamos el alto del rectángulo a partir del valor proporcionado //

	color_rectangulo = color; // Asignamos el color del rectángulo a partir del valor proporcionado //
}

void Rectangulo::dibujar_Rectangulo()
{
    // Mitades del Tamaño // 

    const float half_w = ancho_rectangulo * 0.5f;
    const float half_h = alto_rectangulo * 0.5f;

    // Vértices del Rectángulo //

	const float x_left = centro_rectangulo.x - half_w; // Coordenada X del lado izquierdo del rectángulo //
	const float x_right = centro_rectangulo.x + half_w; // Coordenada X del lado derecho del rectángulo //
	const float y_bottom = centro_rectangulo.y - half_h; // Coordenada Y del lado inferior del rectángulo //
	const float y_top = centro_rectangulo.y + half_h; // Coordenada Y del lado superior del rectángulo //

	// Color del Rectángulo //

	glColor3ub
	(
		(GLubyte)color_rectangulo.color_red,
		(GLubyte)color_rectangulo.color_green,
		(GLubyte)color_rectangulo.color_blue
	);


    // Dibujo del Rectángulo Relleno //

	glBegin(GL_QUADS); // Comienza a dibujar un cuadrilátero //

	glVertex2f(x_left, y_bottom); // Vértice inferior izquierdo del rectángulo //
	glVertex2f(x_right, y_bottom); // Vértice inferior derecho del rectángulo //
	glVertex2f(x_right, y_top); // Vértice superior derecho del rectángulo //
	glVertex2f(x_left, y_top); // Vértice superior izquierdo del rectángulo //

	glEnd(); // Termina de dibujar el cuadrilátero //
}
