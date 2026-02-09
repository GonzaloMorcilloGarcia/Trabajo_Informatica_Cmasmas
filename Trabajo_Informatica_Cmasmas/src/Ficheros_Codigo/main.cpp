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

// DECLARACION DE VARIABLES GLOBALES //

constexpr int VIRTUAL_W = 1920;
constexpr int VIRTUAL_H = 1080;

constexpr int FPS = 60;
constexpr int FRAME_MS = 1000 / FPS;

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

Boton boton_ejemplo 
{
    {VIRTUAL_W/2, VIRTUAL_W/2},
    20, 20,
    {255, 0, 0},
	{0, 0, 0},
	2
};


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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(VIRTUAL_W / 2, VIRTUAL_H / 2);
    glutCreateWindow("Trabajo de Informatica Cmasmas: NOMBRE POR DEFINIR");

    glutDisplayFunc(OnDisplay);
    glutReshapeFunc(OnReshape);
    glutKeyboardFunc(OnKeyboard);
    glutMouseFunc(OnMouse);
    glutPassiveMotionFunc(OnPassiveMouseMotion);

    glClearColor(1.f, 1.f, 1.f, 1.f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    init_Juego();

    glutTimerFunc(FRAME_MS, OnTimer, 0);

    glutMainLoop();

    return 0;
}

// FUNCIONES LOCALES //

void init_Juego ()
{
	// Aquí se pueden inicializar variables, cargar recursos, etc. antes de entrar en el bucle principal //
}

// FUNCIONES DE GLUT //

void OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia la pantalla y el buffer de profundidad //
    
	glViewport(viewport.x, viewport.y, viewport.w, viewport.h); // Establece el viewport actual para que coincida con el área de dibujo del juego, dejando las barras negras a los lados si es necesario //

	glMatrixMode(GL_PROJECTION); // Configura la matriz de proyección para que coincida con las coordenadas virtuales del juego, independientemente del tamaño real de la ventana //

	glLoadIdentity(); // Reinicia la matriz de proyección para que no haya transformaciones acumuladas //

	gluOrtho2D(0, VIRTUAL_W, 0, VIRTUAL_H); // Establece una proyección ortográfica con el origen en la esquina inferior izquierda y las coordenadas que van de 0 a VIRTUAL_W en el eje X y de 0 a VIRTUAL_H en el eje Y //

	glMatrixMode(GL_MODELVIEW); // Configura la matriz de modelo para que esté lista para dibujar los elementos del juego en las coordenadas virtuales //

	glLoadIdentity(); // Reinicia la matriz de modelo para que no haya transformaciones acumuladas //

	// Aquí se pueden dibujar los elementos del juego, el menú, el tablero, etc. dependiendo del estado actual del juego // 

	boton_ejemplo.dibujar_Boton();

	glutSwapBuffers(); // Intercambia los buffers para mostrar lo que se ha dibujado en la pantalla //
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

            if (boton_ejemplo.Contiene_Coordenadas(coordenadas_mouse))
            {
				std::cout << "¡Botón Ejemplo Presionado!" << std::endl;
			}
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