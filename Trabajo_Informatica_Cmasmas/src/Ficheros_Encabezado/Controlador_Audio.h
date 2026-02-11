#pragma once

//INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias de OpenGL //
#include <freeglut.h>

// Otras Librerias //

#include <algorithm> // Para std::min y std::max //
#include <cmath> // Para std::lround //      
#include <iostream> // Para std::cout y std::endl //
#include <vector>
#include "ETSIDI.h"
#include <SFML/Audio.hpp>

// Ficheros de Encabezado //

#include "funciones_globales.h"
#include "Boton.h"

struct Cancion 
{
	std::string nombre_cancion;
	std::string ruta_cancion;

	int duracion_cancion; // Duracion en segundos
	int id_cancion; // Identificador unico para cada cancion

};

class Controlador_Audio
{

public:

    void iniciar_Controlador_Audio();

    inline void anadir_Cancion(const Cancion& c)
    {
        lista_canciones.push_back(c);
    }

    bool reproducir_Cancion (int id, bool loop = true);
    bool reproducir_Cancion (const std::string& nombre, bool loop = true);

    void pausar_Cancion();
    void reanudar_Cancion();
	void toggle_Cancion();

    void detener_Cancion();     
    void reiniciar_Cancion();

	bool anterior_Cancion();
	bool siguiente_Cancion();
	
    void actualizar_Cancion();

    void set_Volumen_Musica(float volumen);
    
    inline float get_Volumen_Musica() const { return volumen_musica; };

    inline int get_Id_Actual() const { return id_actual; };

    std::string get_Nombre_Cancion_Actual() const;


private:

    std::vector<Cancion> lista_canciones;

    sf::Music musica;       // 1 música activa

    int id_actual = 0;

    bool reproduciendo_musica = false;

	bool musica_pausada = false;

    float volumen_musica = 60.f;

    sf::SoundSource::Status estado_anterior = sf::SoundSource::Status::Stopped;

private:

    int buscar_Id (const std::string& nombre) const;

    static float limitador_Volumen (float volumen);
};
