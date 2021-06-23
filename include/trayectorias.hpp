#ifndef TRAYECTORIAS_H
#define TRAYECTORIAS_H
#pragma once

#include <vector>
#include "Vertex.hpp"

using namespace std;

class trayectorias  
{
	private:
	public:
		trayectorias();
		vector<Vertex> lineal(Vertex ini, Vertex end, float dt);
		vector<Vertex> bezier(Vertex ini, Vertex end, float dt);
};
#endif