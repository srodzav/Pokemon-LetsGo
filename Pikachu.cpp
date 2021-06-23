#include "Pikachu.hpp"  
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <armadillo>
#include <GLFW/glfw3.h>
#include <math.h>
#include "Objeto.hpp"

using namespace std;

Pikachu::Pikachu()
{
	
}
Pikachu::Pikachu(Object o, Object p, Object q)
{
	Pokemon1 = o;
	Ball = p;
	Pokemon2 = q;
}
void Pikachu::DibujaPoke1(arma::fmat Mtr_PokemonIzq)
{
	for (Face face : Pokemon1.get_faces())
	{
		for (int index: face.get_vertices())
		{
			Vertex v = Pokemon1.get_vertex()[index];
			arma::fcolvec v_dib = Mtr_PokemonIzq * v.h();
			v_dib = v_dib / v_dib.at(3,0);

			glVertex3f(v_dib.at(0,0), v_dib.at(1,0), v_dib.at(2,0));
		}
	}
}
void Pikachu::DibujaBall(arma::fmat Mtr_Pokeball)
{
	for (Face face2 : Ball.get_faces())
	{
		for (int index2: face2.get_vertices())
		{
			Vertex v = Ball.get_vertex()[index2];
			arma::fcolvec v_dib = Mtr_Pokeball * v.h();
			v_dib = v_dib / v_dib.at(3,0);

			glVertex3f(v_dib.at(0,0), v_dib.at(1,0), v_dib.at(2,0));
		}
	}
}
void Pikachu::DibujaPoke2(arma::fmat Mtr_PokemonDer)
{
	for (Face face : Pokemon2.get_faces())
	{
		for (int index: face.get_vertices())
		{
			Vertex v = Pokemon2.get_vertex()[index];
			arma::fcolvec v_dib = Mtr_PokemonDer * v.h();
			v_dib = v_dib / v_dib.at(3,0);

			glVertex3f(v_dib.at(0,0), v_dib.at(1,0), v_dib.at(2,0));
		}
	}
}