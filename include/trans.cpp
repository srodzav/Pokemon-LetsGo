#include "trans.hpp"  
#include <math.h>
#include "trayectorias.hpp"  

#define PI 3.1416

trans::trans()
{
	
}

arma::fmat trans::T(float dx, float dy, float dz)
{
    arma::fmat Tt ={ {1, 0, 0, dx},
                    {0, 1, 0, dy},
                    {0, 0, 1, dz},
                    {0, 0, 0, 1}};

    return(Tt);
}

arma::fmat trans::S(float sx, float sy, float sz)
{
    arma::fmat St ={ {sx, 0, 0, 0},
                    {0, sy, 0, 0},
                    {0, 0, sz, 0},
                    {0, 0, 0, 1}};
    return(St);
}

arma::fmat trans::Rx(float theta)
{
    float ang = theta * (PI/180);
    arma::fmat Rxt ={   {1, 0, 0, 0},
                        {0, cosf(ang), -sinf(ang), 0},
                        {0, sinf(ang), cosf(ang), 0},
                        {0, 0, 0, 1}};
    return(Rxt);
}

arma::fmat trans::Ry(float theta)
{
    float ang = theta * (PI/180);
    arma::fmat Ryt ={   {cosf(ang), 0, sinf(ang), 0},
                        {0, 1, 0, 0},
                        {-sinf(ang), 0, cosf(ang), 0},
                        {0, 0, 0, 1}};
    return(Ryt);
}

arma::fmat trans::Rz(float theta)
{
    float ang = theta * (PI/180);
    arma::fmat Rzt ={   {cosf(ang), -sinf(ang), 0, 0},
                        {sinf(ang), cosf(ang), 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 1}};
    return(Rzt);
}

arma::fmat trans::Rp1p2(Vertex P1, Vertex P2, float theta)
{
    // Paso 1
    arma::fmat T = {{1, 0, 0, -P1.get_x()},
                    {0, 1, 0, -P1.get_y()},
                    {0, 0, 1, -P1.get_z()},
                    {0, 0, 0, 1}};

    // Paso 2
    float D1 = sqrt(powf(P2.get_x()-P1.get_x(), 2) + powf(P2.get_z()-P1.get_z(), 2));
    arma::fmat Ry = {{(P2.get_z()-P1.get_z())/D1, 0, -(P2.get_x()-P1.get_x())/D1, 0},
                    {0, 1, 0, 0},
                    {(P2.get_x()-P1.get_x())/D1, 0, (P2.get_z()-P1.get_z())/D1, 0},
                    {0, 0, 0, 1}};

    // Paso 3
    float D2 = sqrt(powf(P2.get_x()-P1.get_x(), 2) + powf(P2.get_y()-P1.get_y(), 2));
    arma::fmat Rx = {{1, 0, 0, 0},
                    {0, D1/D2, -(P2.get_y()-P1.get_y())/D2, 0},
                    {0, (P2.get_y()-P1.get_y())/D2, D1/D2, 0},
                    {0, 0, 0, 1}};

    // Paso 4
    arma::fmat Tz_t = (this->Rz(theta));

    // Paso 5
    arma::fmat Rxi = Rx.i();

    // Paso 6
    arma::fmat Ryi = Ry.i();

    // Paso 7
    arma::fmat Ti = T.i();

    arma::fmat MC = Ti * Ryi * Rxi * Tz_t * Rx * Ry * T;
    return (MC);
}