#ifndef VERTEX_H
#define VERTEX_H
#pragma once

#include <armadillo>

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
#endif