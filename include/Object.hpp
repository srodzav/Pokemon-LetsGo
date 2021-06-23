#ifndef OBJECT_H
#define OBJECT_H
#pragma once

#include <string>
#include <vector>
#include "Vertex.hpp"
#include "Face.hpp"

using namespace std;

class Object
{
    private:
		string name;

        vector<Vertex> verts;
        vector<Face> faces;
		vector<int> index;
        vector<string> split(const string& str, const string& delim);
    public:
        Object(string obj_file);
        vector<Vertex> get_vertex();
        vector<Face> get_faces();
        void print();
};
#endif