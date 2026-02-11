#include "Controlador_Audio.h"

void Controlador_Audio::iniciar_Controlador_Audio()
{
    set_Volumen_Musica(volumen_musica);

}

bool Controlador_Audio::reproducir_Cancion (int id, bool loop)
{
 
    if (reproduciendo_musica && id_actual == id)
    {
        musica.setLooping(loop);
        musica.setVolume(volumen_musica);
        musica.play();
        return true;
    }

    musica.stop();

    reproduciendo_musica = false;

    const std::string& ruta = lista_canciones[id].ruta_cancion;

    if (!musica.openFromFile(ruta)) return false;

    id_actual = id;

    reproduciendo_musica = true;

    musica.setLooping(loop);
    musica.setVolume(volumen_musica);
    musica.play();

    return true;
}

bool Controlador_Audio::reproducir_Cancion (const std::string& nombre, bool loop )
{
	int id = buscar_Id(nombre);

    return reproducir_Cancion(id, loop);
}

void Controlador_Audio::pausar_Cancion()
{
    if (reproduciendo_musica && musica.getStatus() == sf::SoundSource::Status::Playing)
        musica.pause();
}

void Controlador_Audio::reanudar_Cancion()
{
    if (reproduciendo_musica && musica.getStatus() == sf::SoundSource::Status::Paused)
        musica.play();
}

void Controlador_Audio::detener_Cancion()
{
    if (reproduciendo_musica)
        musica.stop();
}

void Controlador_Audio::reiniciar_Cancion()
{
    if (reproduciendo_musica) return;
    musica.stop(); // stop vuelve al inicio
    musica.play();
}

bool Controlador_Audio::anterior_Cancion()
{
    id_actual = id_actual - 1;

    if (id_actual < 0) id_actual = (int)lista_canciones.size() - 1;

    return reproducir_Cancion(id_actual, false);
}

bool Controlador_Audio::siguiente_Cancion()
{
    id_actual = id_actual + 1;

    if (id_actual >= (int)lista_canciones.size()) id_actual = 0;

    return reproducir_Cancion(id_actual, false);
}

void Controlador_Audio::actualizar_Cancion()
{
    if (reproduciendo_musica && musica.getStatus() == sf::SoundSource::Status::Stopped && !musica.isLooping())
    {
        siguiente_Cancion();
    }
}

void Controlador_Audio::set_Volumen_Musica(float volumen)
{
    volumen_musica = limitador_Volumen (volumen);

    if (reproduciendo_musica)
        musica.setVolume(volumen_musica);
}

int Controlador_Audio::buscar_Id(const std::string& nombre) const
{
    for ( auto i : lista_canciones )
    {
        if (i.nombre_cancion == nombre) return i.id_cancion;
    }
    return -1; 
}

float Controlador_Audio::limitador_Volumen (float volumen)
{
    if (volumen < 0.f) return 0.f;

    if (volumen > 100.f) return 100.f;
    
    return volumen;
}
