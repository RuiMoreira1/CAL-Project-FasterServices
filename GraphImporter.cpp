#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

#include "GraphImporter.h"

using namespace std;

void GraphImporter::importNodes(Graph<unsigned > *g, ifstream &NodesFile) {
    string line;
    unsigned info;
    double x, y;
    while (getline(NodesFile, line)) {
        istringstream node(line);
        node >> info >> x >> y;


        //g->addVertex(info, x, y);
       // g->addVertex(info,x,y);
    }
}


void GraphImporter::importEdges(Graph<unsigned > *g,ifstream &EdgesFile){
    string line;
    unsigned s, d;
    double w;
    while (getline(EdgesFile, line)) {
        istringstream iss(line);
        iss >> s >> d >> w;

        //g->addEdge(s, d, w);
    }
}

Graph<unsigned> * GraphImporter::importAll(const string NodesFile,const string EdgesFile){
    ifstream nodes_file(NodesFile);
    if (!nodes_file.is_open()) {
    }

    ifstream edges_file(EdgesFile);
    if (!edges_file.is_open()){

    }

    Graph<unsigned> *g = new Graph<unsigned>;

    importNodes(g, nodes_file);
    importEdges(g, edges_file);

    return g;
}