#ifndef FACE_H
#define FACE_H
#pragma once

#include <vector>
#include "Vertex.hpp"

using namespace std;

class Face  
{
	private:
		float A,B,C,D;
		vector <int> vertices;
		vector <Vertex> verts;
		int index;
		int index2;
		int index3;
	public:
		Face(vector<int> vertices);
		vector<int> get_vertices();
		void plano(vector <Vertex> verts, int index, int index2, int index3);
		void print();
};
#endif