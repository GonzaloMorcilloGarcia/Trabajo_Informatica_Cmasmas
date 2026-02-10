//INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias de OpenGL //
#include <freeglut.h>

// Otras Librerias //

#include <algorithm> // Para std::min y std::max //
#include <cmath> // Para std::lround //      
#include <iostream> // Para std::cout y std::endl //

// Ficheros de Encabezado //

#include "funciones_globales.h"
#include "Vector_2D.h"

#include "Rectangulo.h"
#include "Boton.h"
#include "Controlador_Juego.h"

// DECLARACION DE VARIABLES GLOBALES //



// DEFINICIÓN DE ESTRUCTURAS GLOBALES //

struct Viewport 
{ 
    int x{}, y{}, w{1}, h{1};

    static Viewport KeepAspect(int REAL_W, int REAL_H, int VIRTUAL_W, int VIRTUAL_H)
    {
        // Escala uniforme para mantener aspecto VIRTUAL_W:VIRTUAL_H // 

        const float sx = REAL_W / static_cast<float>(VIRTUAL_W);
        const float sy = REAL_H / static_cast<float>(VIRTUAL_H);
        const float s = std::min(sx, sy);

        const int vpW = std::max(1, static_cast<int>(std::lround(VIRTUAL_W * s)));
        const int vpH = std::max(1, static_cast<int>(std::lround(VIRTUAL_H * s)));

        const int vpX = (REAL_W - vpW) / 2;
        const int vpY = (REAL_H - vpH) / 2;

        return { vpX, vpY, vpW, vpH };
    }

    bool ContainsViewport(int coordenada_x, int coordenada_y) const
    {
        return Contiene({coordenada_x, coordenada_y}, x, y, w, h);
    }

    
    bool ScreenToVirtual(int sx, int sy, int REAL_H,int VIRTUAL_W, int VIRTUAL_H,
        Vector_2D& out) const
    {
        const int y_bottom = REAL_H - sy; // convertimos a origen abajo

        if (!ContainsViewport(sx, y_bottom))
            return false; // está en las barras

        const float nx = (sx - x) / static_cast<float>(w);
        const float ny = (y_bottom - y) / static_cast<float>(h);

        out.x = static_cast<int>(std::lround(nx * VIRTUAL_W));
        out.y = static_cast<int>(std::lround(ny * VIRTUAL_H));

        // clamp opcional
        out.x = std::clamp (out.x, 0, VIRTUAL_W);
        out.y = std::clamp (out.y, 0, VIRTUAL_H);

        return true;
    }
};

Viewport viewport{0, 0, 1, 1}; // Variable global para almacenar el viewport actual del juego, que se actualizará en la función de reshape //

// DECLARACION DE CLASES GLOBALES //

Controlador_Juego controlador_juego{};

// PROTOTIPOS DE FUNCIONES DE GLUT //

void OnDisplay();
void OnReshape(int width, int height);
void OnKeyboard(unsigned char key, int x, int y);
void OnTimer(int value);
void OnMouse(int button, int state, int x, int y);
void OnPassiveMouseMotion(int x, int y);

// PROTOTIPOS DE FUNCIONES LOCALES //

void init_Juego();

// FUNCION PRINCIPAL //

int main(int argc, char** argv)
{
    // Inicialización del Programa y la Ventana //

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(VIRTUAL_W / 2, VIRTUAL_H / 2);
    glutCreateWindow("Trabajo de Informatica Cmasmas: NOMBRE POR DEFINIR");

    // Callbacks

    glutDisplayFunc(OnDisplay);
    glutReshapeFunc(OnReshape);
    glutKeyboardFunc(OnKeyboard);
    glutMouseFunc(OnMouse);
    glutPassiveMotionFunc(OnPassiveMouseMotion);

    // Color de fondo

    glClearColor(1.f, 1.f, 1.f, 1.f);

    // 2D: Asegura que NO haya profundidad

    glDisable(GL_DEPTH_TEST); 

    // (opcional, pero recomendado) Desactiva iluminación y texturas en UI 2D

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    // Alpha blending (útil para transparencias)

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Init juego

    init_Juego();

    // Timer

    glutTimerFunc(FRAME_MS, OnTimer, 0);

    glutMainLoop();

    return 0;
}

// FUNCIONES LOCALES //

void init_Juego ()
{
	// Aquí se pueden inicializar variables, cargar recursos, etc. antes de entrar en el bucle principal //

    controlador_juego.iniciar_Controlador();
}

// FUNCIONES DE GLUT //

void OnDisplay()
{
    // 1) Limpia TODA la ventana (barras incluidas) a negro
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 2) Activa el viewport del juego (manteniendo aspecto)
    glViewport(viewport.x, viewport.y, viewport.w, viewport.h);

    // 3) Proyección ortográfica en coordenadas virtuales
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, VIRTUAL_W, 0, VIRTUAL_H);

    // 4) Modelo identidad
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 5) Dibujo del estado actual
    controlador_juego.dibujar_Estado();

    // 6) Swap buffers
    glutSwapBuffers();
}

void OnReshape(int width, int height)
{
	// Ajusta el viewport y la proyección para mantener la relación de aspecto del juego //

    viewport = Viewport::KeepAspect(width, height, VIRTUAL_W, VIRTUAL_H);

	glutPostRedisplay(); // Solicita a GLUT que vuelva a dibujar la pantalla después de ajustar el viewport //
}

void OnKeyboard(unsigned char key, int x, int y)
{
	// Aquí se pueden manejar las entradas del teclado para controlar el juego, navegar por el menú, etc. //

    controlador_juego.actualizar_Estado(key);

    
	glutPostRedisplay(); // Solicita a GLUT que vuelva a dibujar la pantalla después de procesar la entrada del teclado //
}

void OnMouse(int button, int state, int x, int y)
{
    if (state != GLUT_DOWN) return;

    const int REAL_H = glutGet(GLUT_WINDOW_HEIGHT);

    Vector_2D coordenadas_mouse{};

    const bool inside = viewport.ScreenToVirtual(x, y, REAL_H, VIRTUAL_W, VIRTUAL_H, coordenadas_mouse);

    if (button == GLUT_LEFT_BUTTON)
    {
        if (inside)
        {
            // click izquierdo en área de juego (mouseV.x, mouseV.y)

            controlador_juego.actualizar_Estado(coordenadas_mouse, true);
        }
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        if (inside)
        {
            // click derecho en área de juego
        }
    }
}

void OnPassiveMouseMotion(int x, int y)
{
	const int REAL_H = glutGet(GLUT_WINDOW_HEIGHT); // Necesitamos la altura real de la ventana para convertir las coordenadas del mouse a coordenadas virtuales con origen en la esquina inferior izquierda //

	Vector_2D coordenadas_mouse{}; // Variable para almacenar las coordenadas virtuales del mouse después de la conversión //

	const bool inside = viewport.ScreenToVirtual(x, y, REAL_H, VIRTUAL_W, VIRTUAL_H, coordenadas_mouse); // Convierte las coordenadas del mouse a coordenadas virtuales y verifica si están dentro del área de juego (no en las barras negras) //

	if (inside) // Si el mouse está dentro del área de juego, se pueden usar las coordenadas virtuales (coordenadas_mouse.x, coordenadas_mouse.y) para interactuar con el juego, como resaltar casillas, mostrar información, etc. //
    {
		controlador_juego.actualizar_Hover(coordenadas_mouse); // Actualiza el estado de hover del juego con las coordenadas virtuales del mouse //
    }

	glutPostRedisplay(); // Solicita a GLUT que vuelva a dibujar la pantalla después de procesar el movimiento del mouse //
}

void OnTimer(int value)
{
	// Aquí se pueden actualizar las animaciones, el estado del juego, etc. que necesiten ser actualizados periódicamente //

	glutPostRedisplay(); // Solicita a GLUT que vuelva a dibujar la pantalla después de actualizar el estado del juego //

	glutTimerFunc(FRAME_MS, OnTimer, 0); // Vuelve a configurar el temporizador para que se llame a esta función nuevamente después de FRAME_MS milisegundos, creando un bucle de actualización constante //
}

// FIN DEL CÓDIGO //