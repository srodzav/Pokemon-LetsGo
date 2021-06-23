#ifndef OBJETO_HPP
#define OBJETO_HPP

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <armadillo>
#include <GLFW/glfw3.h>

using namespace std;

// CLASE VERTEX
#pragma region VERTEX
class Vertex
{
    private:
        float x,y,z;
    public:
        Vertex();
        Vertex(float xi, float yi, float zi);
        float get_x();
		float get_y();
		float get_z();
        void print();
        arma::fcolvec h();
};
#pragma endregion 

// CLASE FACE
#pragma region FACE
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
#pragma endregion 

// CLASE OBJECT
#pragma region OBJECT
class Object
{
    private:
		string name;
    
        vector<Vertex> verts;
        vector<Face> faces;
		vector<int> index;
        vector<string> split(const string& str, const string& delim);
    public:
		Object();
        Object(string obj_file);
        vector<Vertex> get_vertex();
        vector<Face> get_faces();
        void print();
};
#pragma endregion 

// CLASE TRANS
#pragma region TRANS
class trans
{
	private:

	public:
		trans();
		arma::fmat T(float dx, float dy, float dz);
		arma::fmat S(float sx, float sy, float sz);
		arma::fmat Rx(float theta);
		arma::fmat Ry(float theta);
		arma::fmat Rz(float theta);
		arma::fmat Rp1p2(Vertex P1, Vertex P2, float theta);
};
#pragma endregion 

// CLASE TRAYECTORIAS
#pragma region TRAYECTORIAS
class trayectorias  
{
	private:
	public:
		trayectorias();
		vector<Vertex> lineal(Vertex ini, Vertex end, float dt);
		vector<Vertex> bezier(Vertex ini, Vertex end, float dt);
};
#pragma endregion 

#endif