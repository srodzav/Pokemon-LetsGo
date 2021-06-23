/*
*   Materia: Graficación por Computadora
*   Profesor: Omar Rodríguez Gónzalez
*   Alumno: Jose María Sebastián Rodríguez Zavala
*   
*   Proyecto: Pokémon Let's Go: ¡Pikachu!
*/

#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <armadillo>  
#include "Objeto.hpp" // Junté todas las clases y métodos en un archivo porque me daba error al compilar con los "include/**"
#include "Pikachu.hpp"

// Variables globales
#define Pi 3.141526
#define g 9.81

using namespace std;

#pragma region CABECERAS_FUNCIONES
// Cabeceras de las funciones
void TiroParabolico(float Vo, float Ang, float *DistanciaX, float *DistanciaY, float *Tvuelo);
void getPosXY(float Vx, float Vy, float *temp, float *PosX, float *PosY, float TiempoTotal, float VHigh);
void Trayectoria(float Vx, float Vy, float temp, float *PosX, float *PosY, float TiempoTotal, float VHigh);
void DotPoints(float TiempoTotal, float Vx, float Vy, float Scale);
void Menu();
void getPokemon(char *n);
void getColor(char *Pkmn, double *red, double *green, double *blue);

#pragma endregion

int main()
{
    #pragma region VARIABLES
    // Variables para calcular tiro parabolico
    float Vo = 40.0, Ang = 45.0, DistanciaX, DistanciaY, Tvuelo, PX = 0.0, PY = 0;
    float Vx = Vo * cos(((Ang * Pi) / 180));
    float Vy = Vo * sin(((Ang * Pi) / 180));
    float temp = 0;
    float MovePikaX = 0.0;

    TiroParabolico(Vo, Ang, &DistanciaX, &DistanciaY, &Tvuelo);

    float VHigh = DistanciaX;
    bool boolMovPok1 = true;

    // Variables para dibujar los Pokémon
    double red = 0.0, green = 0.0, blue = 0.0;
    double re = 0.0, gre = 0.0, blu = 0.0;
    
    // Variable para utilizar las transformaciones
    trans tr;
    #pragma endregion

    #pragma region LECTURA DE OBJETOS
    // Función para desplegar el menú completo
    Menu();

    // Variables para guardar los .obj
    char Poke1[80] = "", Poke2[80] = "", obj1[80] = "", obj2[80] = "";

    // Función para obtener el Pokémon deseado
    getPokemon(Poke1);
    getPokemon(Poke2);

    // Función para obtener el color con base al Pokémon
    getColor(Poke1, &red, &green, &blue);
    getColor(Poke2, &re, &gre, &blu);

    // Concatenar obj/ y .obj a los Pokémon
    strcpy(obj1, "obj/");
    strcpy(obj2, "obj/");
    strcat(Poke1, ".obj");
    strcat(Poke2, ".obj");
    strcat(obj1, Poke1);
    strcat(obj2, Poke2);

    // Objetos necesarios
    Object Pokemon1(obj1);
    Object Pokemon2(obj2);
    Object Ball("obj/Pokeball.obj");

    // Creación del "arreglo" de los objetos
    Pikachu Modelo = *new Pikachu(Pokemon1,Ball,Pokemon2);
    #pragma endregion

    #pragma region CREACION DE VENTANA
    // Creación de la ventana
    GLFWwindow* window;

    if( !glfwInit() )
    {
        cout << stderr << "Fallo al inicializar GLFW\n";
        return -1;
    }

    window = glfwCreateWindow(1024, 768, "Pokemon Let's Go", NULL, NULL);
    if( window == NULL ) {
        cout << stderr << "Fallo al abrir la ventana de GLFW.\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    #pragma endregion

    #pragma region PROYECCIONES
    // Proyecciones
    arma::frowvec eye = {0.2, 0.2, 10.0};
    arma::frowvec camera = {0.2, -0.2, 0.0};

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    float ar = width/height;

    // Proyeccion en paralelo
    glViewport(0, 0, width, height);
    glOrtho(-ar, ar, -1.0, 1.0, -20.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    #pragma endregion

    #pragma region DATOS OBTENIDOS
    // Menú de datos obtenidos con base a los calculos
    cout << "\n>> DATOS OBTENIDOS <<" << endl;
    cout << "--------------" << endl;
    cout << "Velocidad en X: " << Vx << endl;
    cout << "Velocidad en Y: " << Vy << endl;
    cout << "Tiempo de vuelo: " << Tvuelo << endl;
    cout << "Distancia total: " << DistanciaX << endl; 
    cout << "Altura maxima: " << DistanciaY << endl;
    cout << "--------------" << endl;
    #pragma endregion

    #pragma region DIBUJADO GLFW
    // Menú principal donde se dibuja todo el proyecto
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    do {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // Vista de frente
        if(glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_RELEASE){
            eye = {-5.0, 1.5, 10.0};
            camera = {0.2, -0.2, 0.0};
        }
        // Vista lateral inclinada
        if(glfwGetKey(window, GLFW_KEY_UP) != GLFW_RELEASE){
            eye = {0.2, 0.2, 10.0};
            camera = {0.2, -0.2, 0.0};
        }
        // Vista lateral inclinada posición contraria
        if(glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_RELEASE){
            eye = {-1.0, 1.5, -10.0};
            camera = {0.2, -0.2, 0.0};
        }
        // Vista lateral frente del bate
        if(glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_RELEASE){
            eye = {8.5, 1.5, 7.5};
            camera = {0.2, -0.2, 0.0};
        }
        gluLookAt(eye[0], eye[1], eye[2], 
                camera[0], camera[1], camera[2], 
                0.0, 1.0, 0.0);
        
        if(boolMovPok1 == false)
            getPosXY(Vx, Vy, &temp, &PX, &PY, Tvuelo, VHigh); // Función para calcular la posición actual
        DotPoints(Tvuelo, Vx, Vy, 0.09); // Función para calcular los puntos del tiro parabolico

        // Calculo de matrices de transformaciones
        arma::fmat Mtr_Poke1 = tr.S(0.45, 0.45, 0.45) * tr.T(-2.0 + MovePikaX, -0.4, 0.0);
        arma::fmat Mtr_Pokeball = tr.S(0.09, 0.09, 0.09) * tr.T(PX, PY, 0.0);
        arma::fmat Mtr_Poke2 = tr.S(0.45, 0.45, 0.45) * tr.T(2, -0.4, 0.0);
        if(-2.0 + MovePikaX < -0.3)
            MovePikaX += 0.01;
        else
            boolMovPok1 = false;

        // Dibujado de modelos
        glBegin(GL_TRIANGLES);
            // Dibujar Pokémon 1
            glColor3f(red, green, blue);
            Modelo.DibujaPoke1(Mtr_Poke1);

            // Dibujar Pokémon 2
            glColor3f(re, gre, blu);
            Modelo.DibujaPoke2(Mtr_Poke2);

            // Dibujar Pokeball
            glColor3f(1.0, 0.69, 0.69);
            Modelo.DibujaBall(Mtr_Pokeball);
        glEnd();
        
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );
    #pragma endregion 

    glfwTerminate();

    return 0;
}

#pragma region FUNCIONES
// Función para mostrar el menú principal
void Menu()
{
    cout << "\n\n" << endl;
    cout << "Bienvenido a la simulación de Pokémon Lets GO" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Porfavor selecciona tu Pokémon y el Pokémon que deseas capturar (porfavor respeta las mayusculas)" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "La lista de Pokémon es la siguiente:" << endl << "> Charizard" << endl << "> Golbat" << endl << "> Ivysaur" << endl << "> Magikarp" << endl << "> Pikachu" << endl << "> Psyduck" << endl << "> Zubat" << endl;
}
// Función para obtener el nombre de los Pokémon
void getPokemon(char *n)
{
    cout << "\nIngresa Pokémon: \n";
    cin >> n;
    // if(n == "NULL" || n != "Charizad" || n != "Golbat" || n != "Ivysaur" || n != "Magikarp" || n != "Pikachu" || n != "Psyduck" || n != "Zubat"){
    //     cout << "Nombre invalido, por favor ingresa un nombre valido" << endl;
    // }
    // cout << n << endl;
}
// Función para obtener el color con base al Pokémon
void getColor(char *Pkmn, double *red, double *green, double *blue)
{
    if(strcmp(Pkmn,"Charizard") == 0 || strcmp(Pkmn,"Magikarp") == 0) {
        *red = 1;
        *green = 0;
        *blue = 0;
    }
    if(strcmp(Pkmn,"Golbat") == 0 || strcmp(Pkmn,"Zubat") == 0) {
        *red = 1;
        *green = 0;
        *blue = 1;
    }
    if(strcmp(Pkmn,"Ivysaur") == 0) {
        *red = 0;
        *green = 1;
        *blue = 0;
    }
    if(strcmp(Pkmn,"Pikachu") == 0 || strcmp(Pkmn,"Psyduck") == 0) {
        *red = 1;
        *green = 1;
        *blue = 0;
    }
}
// Función para calcular el tiro parabolico
void TiroParabolico(float Vo, float Ang, float *DistanciaX, float *DistanciaY, float *Tvuelo)
{
    *Tvuelo = ((2 * Vo) * sin(((Ang * Pi) / 180))) / g;
    *DistanciaX = (powf(Vo, 2)) * (sin(((Ang * Pi * 2) / 180)) / g);
    *DistanciaY = (powf(Vo, 2) * powf(sin(((Ang * Pi) / 180)), 2)) / (2 * g);
}
// Función para obtener los puntos del tiro parabolico
void DotPoints(float TiempoTotal, float Vx, float Vy, float Scale)
{
    float PosiX = 0;
    float PosiY = 0;
    glPointSize(2.0);
    glBegin(GL_POINTS);

    for(float p = 0.0; p < TiempoTotal; p += 0.09){
        Trayectoria(Vx, Vy, p, &PosiX, &PosiY, TiempoTotal, Scale);
        PosiX *= Scale;
        PosiY *= Scale;
        glVertex3d(PosiX, PosiY, 0.0);
    }
    glEnd();
}
// Función para obtener la posicion actual
void getPosXY(float Vx, float Vy, float *temp, float *PosX, float *PosY, float TiempoTotal, float VHigh)
{
    *PosX = (*temp) * Vx;
    *PosX = *PosX * 0.055;
    *PosY = ((*temp) * Vy) - ((g * (powf(*temp, 2))) / 2);
    *PosY = *PosY * 0.055;
    *temp += 0.005;
    if(*temp > TiempoTotal){
        *temp = 0;
    }
}
// Función que complementa el dibujado de la trayectoria
void Trayectoria(float Vx, float Vy, float temp, float *PosX, float *PosY, float TiempoTotal, float VHigh)
{
    *PosX = (temp) * Vx;
    *PosX = *PosX * 0.055;
    *PosY = ((temp) * Vy) - ((g * (powf(temp, 2))) / 2);
    *PosY = *PosY * 0.055;
}
#pragma endregion 