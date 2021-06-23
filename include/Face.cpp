#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Face.hpp"
#include "Vertex.hpp"
#include <armadillo>

using namespace std;

Face::Face(vector<int> verts)
{
    this->vertices = verts;
}

vector <int> Face::get_vertices()
{
    return this->vertices;
}

void Face::plano(vector <Vertex> verts, int v_index, int v_index2, int v_index3){
    
    Vertex vertices;
    arma::frowvec v1 = {verts[v_index-1].get_x(), verts[v_index-1].get_y(), verts[v_index-1].get_z()};
    arma::frowvec v2 = {verts[v_index2-1].get_x(), verts[v_index2-1].get_y(), verts[v_index2-1].get_z()};
    arma::frowvec v3 = {verts[v_index3-1].get_x(), verts[v_index3-1].get_y(), verts[v_index3-1].get_z()};
    
    arma::frowvec NF1 = arma::cross(v2-v1, v3-v1);
    this->A = NF1[0];
    this->B = NF1[1];
    this->C = NF1[2];
    this->D = ((NF1[0]*v2[0])+(NF1[1]*v2[1])+(NF1[2]*v2[2]));
    cout << this->A << this->B << this->C << this->D << endl;
}