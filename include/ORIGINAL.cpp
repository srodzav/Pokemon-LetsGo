#include <iostream>
#include <GLFW/glfw3.h>
#include <armadillo>  
#include "Object.hpp"
#include "trans.hpp"
#include "trayectorias.hpp"

using namespace std;

int main()
{
    #pragma region VENTANA
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
    #pragma endregion

    #pragma region LECTURA DE OBJETOS
    // Cubo unitario
    Object cubo("obj/cube.obj");
    Object cubo2("obj/cube.obj");
    #pragma endregion

    #pragma region CALCULO DE TRAYECTORIAS
    trans tr;
    trayectorias ty;

    Vertex vi = Vertex(-0.5, -0.5, 0.0);
    Vertex vf = Vertex(0.5, 0.5, 0.0);
    vector <Vertex> linea = ty.lineal(vi, vf, 0.001);
    int numero = linea.size()-1;
    int ind_linea = 0;

    Vertex vi2 = Vertex(-0.8, -0.8, 0.0);
    Vertex vf2 = Vertex(0.8, 0.8, 0.0);
    vector <Vertex> linea2 = ty.lineal(vi2, vf2, 0.01);
    int numero2 = linea.size()-1;
    int ind_linea2 = 0;

    float ang = 0.0;
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    #pragma endregion 

    #pragma region DIBUJADO GLFW
    do {
        Vertex vl = linea[ind_linea];
        if (ind_linea < numero) 
            ind_linea++;
        Vertex vl2 = linea2[ind_linea2];
        if (ind_linea2 < numero2) 
            ind_linea2++;

        arma::fmat Mtr =  tr.T(vl.get_x(),  vl.get_y(),  vl.get_z())  * tr.S(0.25, 0.25, 0.25) * tr.Rx(45) * tr.Ry(ang);
        arma::fmat Mtr2 = tr.T(vl2.get_x(), vl2.get_y(), vl2.get_z()) * tr.S(0.25, 0.25, 0.25) * tr.Rx(45) * tr.Ry(ang);

        glClear( GL_COLOR_BUFFER_BIT );

        glBegin(GL_TRIANGLES);
            glColor3f(1.0, 0.0, 0.0);
            // glVertex3f(-0.3, 0.0, 0.0);
            // glVertex3f(0.3, 0.0, 0.0);
            // glVertex3f(0.0, 0.6, 0.0);
        
        // Dibujar cubo 1
        for (Face face : cubo.get_faces())
        {
            for (int index: face.get_vertices())
            {
                Vertex v = cubo.get_vertex()[index];
                arma::fcolvec v_dib = Mtr * v.h();
                v_dib = v_dib / v_dib.at(3,0);

                glVertex3f(v_dib.at(0,0), v_dib.at(1,0), v_dib.at(2,0));
            }
        }

        // Dibujar cubo 2
        for (Face face2 : cubo2.get_faces())
        {
            for (int index2: face2.get_vertices())
            {
                Vertex v2 = cubo2.get_vertex()[index2];
                arma::fcolvec v_dib2 = Mtr2 * v2.h();
                v_dib2 = v_dib2 / v_dib2.at(3,0);

                glVertex3f(v_dib2.at(0,0), v_dib2.at(1,0), v_dib2.at(2,0));
            }
        }
        glEnd();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        if(ang >= 360)
            ang = 0.0;
        else
            ang += 2.0;

    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
    #pragma endregion 

    glfwTerminate();

    return 0;
}
