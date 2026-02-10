#include "funciones_globales.h"

void dibujar_Fondo(GLuint texId)
{
    if (texId == 0) return;

    // Tamaño REAL del viewport activo (el que tengas puesto con glViewport)
    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    const float vpW = (float)vp[2];
    const float vpH = (float)vp[3];

    // Aspectos
    const float vpAspect = vpW / vpH;
    const float imgAspect = (float)VIRTUAL_W / (float)VIRTUAL_H; // 16:9

    // UV para "cover" (crop centrado)
    float u0 = 0.f, v0 = 0.f, u1 = 1.f, v1 = 1.f;

    if (vpAspect > imgAspect)
    {
        // viewport más ancho -> recorta arriba/abajo
        const float scale = imgAspect / vpAspect;
        const float cut = (1.f - scale) * 0.5f;
        v0 = cut; v1 = 1.f - cut;
    }
    else if (vpAspect < imgAspect)
    {
        // viewport más "alto" -> recorta izquierda/derecha
        const float scale = vpAspect / imgAspect;
        const float cut = (1.f - scale) * 0.5f;
        u0 = cut; u1 = 1.f - cut;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);
    glDisable(GL_LIGHTING);
    glColor3f(1.f, 1.f, 1.f);

    // Flip vertical (ETSIDI)
    glBegin(GL_QUADS);
    glTexCoord2f(u0, v1); glVertex2f(0.f, 0.f);
    glTexCoord2f(u1, v1); glVertex2f((float)VIRTUAL_W, 0.f);
    glTexCoord2f(u1, v0); glVertex2f((float)VIRTUAL_W, (float)VIRTUAL_H);
    glTexCoord2f(u0, v0); glVertex2f(0.f, (float)VIRTUAL_H);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
