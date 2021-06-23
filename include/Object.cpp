#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Vertex.hpp"
#include "Face.hpp"
#include "Object.hpp"

using namespace std;

Object::Object(string obj_file)
{
    string linea; // Variable STRING para editar

    ifstream archivoOBJ(obj_file); // Abre el archivo OBJ
    while(getline (archivoOBJ, linea)) // Va guardando texto(lineas) en linea
    {
        vector<string> elems = this->split(linea," "); // Separa mientras encuentre espacio
        if(elems.size() > 0) // Si elems tiene algo
        {
            if(elems[0].compare("g") == 0) // Si elems enguentra un G
            {
                this->name = elems[1]; // Se guarda en el nombre
            }
            if(elems[0].compare("v") == 0) // Si encuentra un V (vertice)
            {
                float x = stof(elems[1]); // Se guarda X, Y, Z pero convierte string -> float
                float y = stof(elems[2]);
                float z = stof(elems[3]);
                Vertex newv(x,y,z); // Crea un vertice con X, Y, Z ya en float
                this->verts.push_back(newv); // Va agregando el vector a una "cola" que se va a sumar
            }
            if(elems[0].compare("f") == 0) // Si encuentra una F (cara)
            {
                vector<int> vertices;
                for (int i = 1; i < elems.size(); i++)
                {
                    int v_index = stoi(this->split(elems[i],"/")[0]);
                    vertices.push_back(v_index-1); // PARA EL EJEMPLO DEL RECUADRO SE RESTO -1
                }
                //Crear Faces
                Face f(vertices); // Crea una cara con los 3 bordes
                this->faces.push_back(f); // Envia la cara a la "cola" para sumar
            }
        }
    }
}

vector<string> Object::split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if(!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length()); 
    return tokens;
}

void Object::print(){
    cout << "g" << this->name << endl;
    for(Vertex Vertex : this->verts){
        cout << "v " << Vertex.get_x() << "  " << Vertex.get_y() << "  " << Vertex.get_z() << endl;
    }
    for (Face face : this->faces)
    {
        cout << "f";
        for (int index : face.get_vertices())
        {
            cout << index << " ";
        }
        cout << "\n" << endl;
        face.plano(verts, face.get_vertices()[0], face.get_vertices()[1], face.get_vertices()[2]);
    }
    
}

vector<Vertex> Object::get_vertex()
{
    return(this->verts);
}

vector<Face> Object::get_faces()
{
    return(this->faces);
}