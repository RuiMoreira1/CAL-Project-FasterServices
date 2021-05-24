#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

#include "GraphImporter.h"

using namespace std;

GraphImporter::GraphImporter() {};

void GraphImporter::importNodes(Graph<unsigned > *g, ifstream &NodesFile) {
    string line;
    unsigned info;
    double x, y , z;
    int i = 0;
    while (getline(NodesFile, line)) {
        istringstream node(line);
        if(i== 0){
            node >> z;
            i = 1;
        }
        node >> info >> x >> y;
        cout << info << x << y;


        //g->addVertex(info, x, y);
       g->addVertex(info,x,y);
    }
}


void GraphImporter::importEdges(Graph<unsigned > *g,ifstream &EdgesFile){
    string line;
    unsigned s, d,z;
    double w;
    int i = 0;
    while (getline(EdgesFile, line)) {
        istringstream iss(line);
        if(i==0){
            iss >> z;
        }
        iss >> s >> d;

        g->addEdge(s,d);
    }
}

Graph<unsigned> * GraphImporter::importAll(const string NodesFile,const string EdgesFile){
    ifstream nodes_file(NodesFile);
    if (!nodes_file.is_open()) {
        cout << "nothing";
    }

    ifstream edges_file(EdgesFile);
    if (!edges_file.is_open()){
        cout << "nothing";

    }

    Graph<unsigned> *g = new Graph<unsigned>;

    importNodes(g, nodes_file);
    importEdges(g, edges_file);

    return g;
}