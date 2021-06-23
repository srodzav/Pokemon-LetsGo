#ifndef PIKACHU_H
#define PIKACHU_H

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <armadillo>
#include <GLFW/glfw3.h>
#include <math.h>
#include "Objeto.hpp"

class Pikachu  
{
	private:
		Object Pokemon1;
		Object Ball;
		Object Pokemon2;
	public:

		Pikachu();
		Pikachu(Object o, Object p, Object q);
		void DibujaPoke1(arma::fmat Mtr_PokemonIzq);
		void DibujaBall(arma::fmat Mtr_Pokeball);
		void DibujaPoke2(arma::fmat Mtr_PokemonDer);
};
#endif