#include "Objeto.hpp"
#include <iostream>
#include <armadillo>
#include <GLFW/glfw3.h>

#define PI 3.1416

using namespace std;

// FUNCIONES VERTEX
#pragma region VERTEX
Vertex::Vertex()
{
    x = y = z = 0.0;
}
Vertex::Vertex(float xi, float yi, float zi)
{
    x = xi;
    y = yi;
    z = zi;
}
float Vertex::get_x(){
    return this->x;
}
float Vertex::get_y(){
    return this->y;
}
float Vertex::get_z(){
    return this->z;
}
arma::fcolvec Vertex::h()
{
    arma::fcolvec h = {this->x, this->y, this->z, 1};

    return h;
}
void Vertex::print()
{
    cout << "(" << this->x << this->y << this->z << ")" << endl;
}
#pragma endregion 

// FUNCIONES FACE
#pragma region FACE
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
#pragma endregion 

// FUNCIONES OBJECT
#pragma region OBJECT
Object::Object(){}
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
#pragma endregion 

// FUNCIONES TRANS
#pragma region TRANS
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
#pragma endregion 

// FUNCIONES TRAYECTORIAS
#pragma region TRAYECTORIAS
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
#pragma endregion 
