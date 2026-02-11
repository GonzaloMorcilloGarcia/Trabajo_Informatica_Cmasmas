#include "Controlador_Audio.h"

void Controlador_Audio::iniciar_Controlador_Audio()
{
	//lista_canciones.push_back({ "Musica_Batalla", "Audio/musica_batalla.wav", 150, -1 });
	//lista_canciones.push_back({ "Musica_Titulo", "Audio/musica_fondo.wav", 120, 0 });
}

void Controlador_Audio::reproducir_Cancion(const std::string& ruta_cancion)
{
	ETSIDI::playMusica(ruta_cancion.c_str(), -1);
}