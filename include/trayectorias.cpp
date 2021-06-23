#include "trayectorias.hpp"  
#include "Vertex.hpp"
	
trayectorias::trayectorias()
{
	
}

vector<Vertex> trayectorias::lineal(Vertex ini, Vertex end, float dt) 
{// v1 + t(v2 - v1)
    vector <Vertex> line;
    //line.push_back(ini);
    for (float t = 0.0; t < 1.0+dt; t += dt)
    {
        float xl = ini.get_x() + (t * (end.get_x()-ini.get_x()));
        float yl = ini.get_y() + (t * (end.get_y()-ini.get_y()));
        float zl = ini.get_z() + (t * (end.get_z()-ini.get_z()));
        Vertex p(xl, yl, zl);
        line.push_back(p);
    }
    return (line);
}