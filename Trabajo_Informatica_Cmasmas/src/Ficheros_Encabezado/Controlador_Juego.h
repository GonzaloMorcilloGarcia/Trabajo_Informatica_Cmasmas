#pragma once
class Controlador_Juego
{
	enum class Estados_Juego
	{
		// Estados Principales del Juego //

		PANTALLA_TITULO,
		PANTALLA_MENU,
		PANTALLA_TABLERO,
		PANTALLA_BATALLA,
		PANTALLA_PAUSA,

		// Estados de Victoria o Derrota //

		PANTALLA_WIN,
		PANTALLA_GAME_OVER,
	
		// Estados de Ajustes y Creditos //

		PANTALLA_AJUSTES,
		PANTALLA_CREDITOS
	};

public:

	void iniciar_Controlador();

	void dibujar_Estado();

	void actualizar_Estado();

	Estados_Juego get_Estado_Actual() const { return Estado_Actual; }

private:

	Estados_Juego Estado_Actual;

	
};

