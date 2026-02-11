#include "Controlador_Juego.h"


void Controlador_Juego::iniciar_Controlador()
{
	Estado_Actual = Estados_Juego::PANTALLA_TITULO;

	 Fondo_Pantalla_Titulo = ETSIDI::getTexture("assets/imagenes/Pantalla_Titulo.png").id;
	 Fondo_Pantalla_Menu = ETSIDI::getTexture("assets/imagenes/Pantalla_Menu.png").id;
	 Fondo_Pantalla_Tablero = ETSIDI::getTexture("assets/imagenes/Pantalla_Fondo.png").id;
	 Fondo_Pantalla_Batalla = ETSIDI::getTexture("assets/imagenes/Pantalla_Batalla.png").id;


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
			{350, 870},
			560, 120,
			{165, 92, 40},
			10,
			"JUGAR"
		};

		Boton_Ajustes =
		{
			{350, 705},
			560, 120,
			{165, 92, 40},
			10,
			"AJUSTES"
		};

		Boton_Salir =
		{
			{350, 540},
			560, 120,
			{165, 92, 40},
			10,
			"SALIR"
		};

		Boton_Musica =
		{
			{350, 375},
			560, 120,
			{165, 92, 40},
			10,
			"MUSICA"
		};

		// Controles abajo izquierda (fila)

		Boton_Anterior =
		{
			{155, 210},
			170, 120,
			{165, 92, 40},
			8,
			"<-"
		};

		Boton_Pausa =
		{
			{350, 210},
			170, 120,
			{165, 92, 40},
			8,
			"||"
		};

		Boton_Siguiente =
		{
			{545, 210},
			170, 120,
			{165, 92, 40},
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
			{350, 870},
			560, 120,
			{165, 92, 40},
			5,
			"MENU PRINCIPAL"
		};

		Boton_Creditos =
		{
			{350, 705},
			560, 120,
			{165, 92, 40},
			5,
			"CREDITOS"
		};
			Boton_Salir =
		{
			{350, 540},
			560, 120,
			{165, 92, 40},
			5,
			"SALIR"
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
		dibujar_Fondo(Fondo_Pantalla_Titulo);

		break;
	}

	case Estados_Juego::PANTALLA_MENU:
	{
		dibujar_Fondo(Fondo_Pantalla_Menu);

		Boton_Jugar.dibujar_Boton();
		Boton_Ajustes.dibujar_Boton();
		Boton_Salir.dibujar_Boton();
		Boton_Musica.dibujar_Boton();
		Boton_Anterior.dibujar_Boton();
		Boton_Pausa.dibujar_Boton();
		Boton_Siguiente.dibujar_Boton();

		break;

	}

	case Estados_Juego::PANTALLA_TABLERO:
	{
		dibujar_Fondo(Fondo_Pantalla_Tablero);

		break;
	}

	case Estados_Juego::PANTALLA_BATALLA:
	{
		dibujar_Fondo(Fondo_Pantalla_Batalla);

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
		dibujar_Fondo(Fondo_Pantalla_Menu);

		Boton_Menu_Principal.dibujar_Boton();
		Boton_Creditos.dibujar_Boton();
		Boton_Salir.dibujar_Boton();

		break;
	}

	case Estados_Juego::PANTALLA_CREDITOS:
	{		
			dibujar_Fondo(Fondo_Pantalla_Menu);

			void* fuenteTitulo = GLUT_BITMAP_TIMES_ROMAN_24;
			void* fuenteTexto = GLUT_BITMAP_HELVETICA_18;

			glColor3ub(245, 235, 210);

			// Margen izquierdo más pegado
			float x = 80.0f;

			// Altura inicial más arriba
			float y = VIRTUAL_H - 120.0f;

			const float saltoGrande = 100.0f;   // separación entre bloques
			const float saltoNormal = 60.0f;   // separación entre líneas normales

			// ----- TÍTULO -----
			escribe_BitmapText("CABALLOS VS CABALLAS", x, y, fuenteTitulo);
			y -= saltoGrande;

			escribe_BitmapText("CREDITOS", x, y, fuenteTexto);
			y -= saltoGrande;

			// ----- BLOQUE 1 -----
			escribe_BitmapText("Arquitectos del Caos Equino y Marino", x, y, fuenteTexto);
			y -= saltoNormal;

			escribe_BitmapText("Felipe Arrierro Serrano", x + 30, y, fuenteTexto);
			y -= saltoNormal;

			escribe_BitmapText("Gonzalo Morcillo Garcia", x + 30, y, fuenteTexto);
			y -= saltoNormal;

			escribe_BitmapText("Jiahao Li Huang", x + 30, y, fuenteTexto);
			y -= saltoNormal;

			escribe_BitmapText("[Nombre 4]", x + 30, y, fuenteTexto);
			y -= saltoNormal;

			escribe_BitmapText("[Nombre 5]", x + 30, y, fuenteTexto);
			y -= saltoGrande;

			// ----- BLOQUE 2 -----
			escribe_BitmapText("Imagenes y Recursos Visuales", x, y, fuenteTexto);
			y -= saltoNormal;

			escribe_BitmapText("Generados con IA (ChatGPT)", x + 30, y, fuenteTexto);
			y -= saltoGrande;

			// ----- BLOQUE 3 -----
			escribe_BitmapText("Banda Sonora Original", x, y, fuenteTexto);
			y -= saltoNormal;

			escribe_BitmapText("Generada con IA (Suno)", x + 30, y, fuenteTexto);
			y -= saltoGrande;

		break;
	}

	default:
	{
		break;
	}
	}
}

void Controlador_Juego::actualizar_Estado(unsigned char key)
{
	if (Estado_Actual == Estados_Juego::PANTALLA_TITULO)
	{
		cambiar_Estado(Estados_Juego::PANTALLA_MENU);
	}

	else if (Estado_Actual == Estados_Juego::PANTALLA_MENU)
	{
		if (key == 27) // Escape
		{
			cambiar_Estado(Estados_Juego::PANTALLA_AJUSTES);
		}
	}

	else if (Estado_Actual == Estados_Juego::PANTALLA_AJUSTES)
	{
		if (key == 27) // Escape
		{
			cambiar_Estado(Estados_Juego::PANTALLA_MENU);
		}
	}

	else if (Estado_Actual == Estados_Juego::PANTALLA_CREDITOS)
	{
		if (key == 27) // Escape
		{
			cambiar_Estado(Estados_Juego::PANTALLA_AJUSTES);
		}
	}

	else if (Estado_Actual == (Estados_Juego::PANTALLA_TABLERO)|| Estado_Actual == (Estados_Juego::PANTALLA_BATALLA) )
	{
		if (key == 27) // Escape
		{
			cambiar_Estado(Estados_Juego::PANTALLA_PAUSA);
		}
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