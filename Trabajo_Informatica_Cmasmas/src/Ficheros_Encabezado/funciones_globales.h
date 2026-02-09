#pragma once

inline bool Contiene(int coordenada_x, int coordenada_y, int limite_x, int limite_y, int limite_w, int limite_h)
{
    return (coordenada_x >= limite_x && coordenada_x < limite_x + limite_w && coordenada_y >= limite_y && coordenada_y < limite_y + limite_h);
}
