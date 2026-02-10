#include "Controlador_Juego.h"


void Controlador_Juego::iniciar_Controlador()
{
	Estado_Actual = Estados_Juego::PANTALLA_TITULO;

	iniciar_Estado();
}

void Controlador_Juego::cambiar_Estado(Estados_Juego estado_siguiente)
{
	Estado_Actual = estado_siguiente;
	
	iniciar_Estado();

	std::cout << "Estado cambiado \n";
}

void Controlador_Juego::iniciar_Estado()
{
	switch (Estado_Actual)
	{
	case Estados_Juego::PANTALLA_TITULO:
	{
		break;

	}

	case Estados_Juego::PANTALLA_MENU:
	{
		Boton_Jugar =
		{
			{310, 870},
			560, 120,
			{0, 255, 0},
			10,
			"Jugar"
		};

		Boton_Ajustes =
		{
			{310, 705},
			560, 120,
			{0, 255, 0},
			10,
			"Ajustes"
		};

		Boton_Salir =
		{
			{310, 540},
			560, 120,
			{0, 255, 0},
			10,
			"Salir"
		};

		Boton_Musica =
		{
			{310, 375},
			560, 120,
			{0, 255, 0},
			10,
			"Musica"
		};

		// Controles abajo izquierda (fila)

		Boton_Anterior =
		{
			{115, 210},
			170, 120,
			{0, 255, 0},
			8,
			"<-"
		};

		Boton_Pausa =
		{
			{310, 210},
			170, 120,
			{0, 255, 0},
			8,
			"||"
		};

		Boton_Siguiente =
		{
			{505, 210},
			170, 120,
			{0, 255, 0},
			8,
			"->"
		};

		break;
	}

	case Estados_Juego::PANTALLA_TABLERO:
	{
		break;
	}

	case Estados_Juego::PANTALLA_BATALLA:
	{
		break;
	}

	case Estados_Juego::PANTALLA_PAUSA:
	{
		break;
	}

	case Estados_Juego::PANTALLA_WIN:
	{
		break;
	}

	case Estados_Juego::PANTALLA_GAME_OVER:
	{
		break;
	}

	case Estados_Juego::PANTALLA_AJUSTES:
	{
		Boton_Menu_Principal = 
		{
			{VIRTUAL_W/2, VIRTUAL_H/2},
			200, 50,
			{0, 255, 0},
			5,
			"Menu Principal"
		};

		Boton_Creditos =
		{
			{VIRTUAL_W/2, VIRTUAL_H/2 - 100},
			200, 50,
			{0, 255, 0},
			5,
			"Créditos"
		};
			Boton_Salir =
		{
			{VIRTUAL_W/2, VIRTUAL_H/2 - 200},
			200, 50,
			{0, 255, 0},
			5,
			"Salir"
		};

			break;
	}

	case Estados_Juego::PANTALLA_CREDITOS:
	{
		break;
	}

	default:
	{
		break;
	}

	}
}

void Controlador_Juego::dibujar_Estado()
{
	switch (Estado_Actual)
	{
	case Estados_Juego::PANTALLA_TITULO:
	{

	}

	case Estados_Juego::PANTALLA_MENU:
	{
		Boton_Jugar.dibujar_Boton();
		Boton_Ajustes.dibujar_Boton();
		Boton_Salir.dibujar_Boton();
		Boton_Musica.dibujar_Boton();
		Boton_Anterior.dibujar_Boton();
		Boton_Pausa.dibujar_Boton();
		Boton_Siguiente.dibujar_Boton();
	}

	case Estados_Juego::PANTALLA_TABLERO:
	{

	}

	case Estados_Juego::PANTALLA_BATALLA:
	{

	}

	case Estados_Juego::PANTALLA_PAUSA:
	{

	}

	case Estados_Juego::PANTALLA_WIN:
	{

	}

	case Estados_Juego::PANTALLA_GAME_OVER:
	{

	}

	case Estados_Juego::PANTALLA_AJUSTES:
	{

	}

	case Estados_Juego::PANTALLA_CREDITOS:
	{

	}

	default:
	{

	}
	}
}

void Controlador_Juego::actualizar_Estado(unsigned char key)
{
	if (Estado_Actual == Estados_Juego::PANTALLA_TITULO)
	{
		cambiar_Estado(Estados_Juego::PANTALLA_MENU);
	}
}

void Controlador_Juego::actualizar_Estado(Vector_2D coordenadas_mouse, bool leftClick)
{
	// 1) En la pantalla de título: cualquier click (izq/der) vale para pasar al menú
	if (Estado_Actual == Estados_Juego::PANTALLA_TITULO)
	{
		cambiar_Estado(Estados_Juego::PANTALLA_MENU);
		return;
	}

	// 2) Para interactuar con botones, exigimos click izquierdo
	if (!leftClick) return;

	// 3) Menú principal
	if (Estado_Actual == Estados_Juego::PANTALLA_MENU)
	{
		if (Boton_Jugar.Contiene_Coordenadas(coordenadas_mouse))
		{
			cambiar_Estado(Estados_Juego::PANTALLA_TABLERO);

			return;
		}
		if (Boton_Ajustes.Contiene_Coordenadas(coordenadas_mouse))
		{
			cambiar_Estado(Estados_Juego::PANTALLA_AJUSTES);

			return;
		}
		if (Boton_Salir.Contiene_Coordenadas(coordenadas_mouse))
		{
			std::exit(0);
		}
		return;
	}

	// 4) Ajustes
	if (Estado_Actual == Estados_Juego::PANTALLA_AJUSTES)
	{
		if (Boton_Menu_Principal.Contiene_Coordenadas(coordenadas_mouse))
		{
			cambiar_Estado(Estados_Juego::PANTALLA_MENU);
			return;
		}
		if (Boton_Creditos.Contiene_Coordenadas(coordenadas_mouse))
		{
			cambiar_Estado(Estados_Juego::PANTALLA_CREDITOS);
			return;
		}
		if (Boton_Salir.Contiene_Coordenadas(coordenadas_mouse))
		{
			std::exit(0);
		}
		return;
	}

}

void Controlador_Juego::actualizar_Hover(Vector_2D coordenadas_mouse)
{
	if (Estado_Actual == Estados_Juego::PANTALLA_MENU)
	{
		Boton_Jugar.actualizar_Hover(coordenadas_mouse);
		Boton_Ajustes.actualizar_Hover(coordenadas_mouse);
		Boton_Salir.actualizar_Hover(coordenadas_mouse);
		Boton_Musica.actualizar_Hover(coordenadas_mouse);
		Boton_Anterior.actualizar_Hover(coordenadas_mouse);
		Boton_Pausa.actualizar_Hover(coordenadas_mouse);
		Boton_Siguiente.actualizar_Hover(coordenadas_mouse);
	}
	if (Estado_Actual == Estados_Juego::PANTALLA_AJUSTES)
	{
		Boton_Menu_Principal.actualizar_Hover(coordenadas_mouse);
		Boton_Creditos.actualizar_Hover(coordenadas_mouse);
		Boton_Salir.actualizar_Hover(coordenadas_mouse);
	}
}