#include "Controlador_Audio.h"

void Controlador_Audio::iniciar_Controlador_Audio()
{
    set_Volumen_Musica(volumen_musica);

    Cancion Titulo{ "Caballos vs Caballas", "assets/sonidos/Banda_Sonora/Caballos_vs_Caballas.ogg", 2 * 60 + 52, 0 };
    Cancion Menu{ "Menu", "assets/sonidos/Banda_Sonora/Menu_Track.ogg", 5 * 60 + 44, 1 };
    Cancion Tablero{ "El Ataque de las Coces", "assets/sonidos/Banda_Sonora/El_Ataque_de_las_Coces.ogg", 4 * 60 + 4, 2 };
    Cancion Relleno_1{ "La Venganza de los Fish", "assets/sonidos/Banda_Sonora/La_Venganza_de_los_Fish.ogg", 4 * 60 + 22, 3 };
    Cancion Relleno_2{ "Caballas y Furiosas", "assets/sonidos/Banda_Sonora/Caballas_y_Furiosas.ogg", 2 * 60 + 39, 4 };
    Cancion Batalla_1{ "Retro-Herradura", "assets/sonidos/Banda_Sonora/Retro-Herradura.ogg", 6 * 60 + 41, 5 };
    Cancion Batalla_2{ "Furia Equina", "assets/sonidos/Banda_Sonora/Furia_Equina.ogg", 6 * 60 + 47, 6 };

    anadir_Cancion(Titulo);
    anadir_Cancion(Menu);
    anadir_Cancion(Tablero);
    anadir_Cancion(Relleno_1);
    anadir_Cancion(Relleno_2);
    anadir_Cancion(Batalla_1);
	anadir_Cancion(Batalla_2);

    reproduciendo_musica = false;

    id_actual = 0;

    estado_anterior = sf::SoundSource::Status::Stopped;
}

bool Controlador_Audio::reproducir_Cancion (int id, bool loop)
{
    if (id < 0 || id >= (int)lista_canciones.size())
        return false;
 
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

    if (!musica.openFromFile(ruta))
    {
        std::cout << "Error abriendo: " << ruta << std::endl;

        return false;
    }

    id_actual = id;

    musica.setLooping(loop);
    musica.setVolume(volumen_musica);
    musica.play();

    reproduciendo_musica = true;

    estado_anterior = sf::SoundSource::Status::Playing;

    return true;
}

bool Controlador_Audio::reproducir_Cancion (const std::string& nombre, bool loop )
{
	int id = buscar_Id(nombre);

    if (id < 0) return false;

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

void Controlador_Audio::toggle_Cancion()
{
    auto estado = musica.getStatus();

    if (estado == sf::SoundSource::Status::Playing)
    {
        pausar_Cancion();
    }
    else if (estado == sf::SoundSource::Status::Paused)
    {
        reanudar_Cancion();
    }
        
}

void Controlador_Audio::detener_Cancion()
{
    if (!reproduciendo_musica) return;

    musica.stop();

    reproduciendo_musica = false;

    estado_anterior = sf::SoundSource::Status::Stopped;
}

void Controlador_Audio::reiniciar_Cancion()
{
    if (!reproduciendo_musica) return;

    musica.stop();

    musica.play();
}

bool Controlador_Audio::anterior_Cancion()
{
    if (lista_canciones.empty()) return false;

    int anterior = id_actual - 1;

    if (anterior < 0) anterior = (int)lista_canciones.size() - 1;

    return reproducir_Cancion(anterior, false);
}

bool Controlador_Audio::siguiente_Cancion()
{
    int siguiente = id_actual + 1;

    if (siguiente >= (int)lista_canciones.size()) siguiente = 0;

    if (reproducir_Cancion(siguiente, false))
    {
        id_actual = siguiente;
        return true;
    }
    return false;
}

void Controlador_Audio::actualizar_Cancion()
{
    if (lista_canciones.empty()) return;

    auto estado = musica.getStatus();

    if (estado_anterior == sf::SoundSource::Status::Playing && estado == sf::SoundSource::Status::Stopped && !musica.isLooping())
    {
        siguiente_Cancion();
    }

    estado_anterior = estado;
}

void Controlador_Audio::set_Volumen_Musica(float volumen)
{
    volumen_musica = limitador_Volumen (volumen);

    if (reproduciendo_musica)
        musica.setVolume(volumen_musica);
}

int Controlador_Audio::buscar_Id(const std::string& nombre) const
{
    for ( const auto& i : lista_canciones )
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

std::string Controlador_Audio::get_Nombre_Cancion_Actual() const
{
    if (lista_canciones.empty()) return "";

    if (id_actual < 0 || id_actual >= (int)lista_canciones.size())
        return "";

    return lista_canciones[id_actual].nombre_cancion;
}

