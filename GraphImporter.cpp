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
    char c;
    int i = 0;
    while (getline(NodesFile, line)) {
        istringstream node(line);
        if(i== 0){
            node >> z;
            i = 1;
            continue;
        }
        node >>c>> info >>c >> x >>c >> y >>c;
        //cout << info<< " " << x<< " " << y<< endl;


        //g->addVertex(info, x, y);
       g->addVertex(info,x,y);
       i++;
    }
    //cout << i << endl;
}


void GraphImporter::importEdges(Graph<unsigned > *g,ifstream &EdgesFile){
    string line;
    unsigned s, d,z;
    double w;
    char c;
    int i = 0;
    while (getline(EdgesFile, line)) {
        istringstream iss(line);
        if(i==0){
            iss >> z;
            i = 1;
            continue;
        }
        iss >>c >> s >>c >> d >>c;
        //cout << s<< " " << d<< " " << endl;

        g->addEdge(s,d);
        g->addEdge(d,s);
        i++;
    }
    //cout << i;
}

Graph<unsigned> * GraphImporter::importAll(const string NodesFile,const string EdgesFile,const string WorkersFile, const string G_CFile, const string BusStopsFile){
    ifstream nodes_file(NodesFile);
    if (!nodes_file.is_open()) {
        cout << "nothing1";
    }

    ifstream edges_file(EdgesFile);
    if (!edges_file.is_open()){
        cout << "nothing2";

    }

    ifstream workers_file(WorkersFile);
    if (!workers_file.is_open()){
        cout << "nothing3";

    }
    ifstream g_c_file(G_CFile);
    if (!g_c_file.is_open()){
        cout << "nothing3";

    }

    ifstream busStops_file(BusStopsFile);
    if (!busStops_file.is_open()){
        cout << "nothing4";

    }

    Graph<unsigned> *g = new Graph<unsigned>;

    importNodes(g, nodes_file);
    importEdges(g, edges_file);
    importWorkers(g, workers_file);
    importG_C(g,g_c_file);
    importBusStops(g,busStops_file);

    return g;
}

void GraphImporter::importWorkers(Graph<unsigned > *g, ifstream &WorkersFile) {
    string line;
    unsigned info;

    while (getline(WorkersFile, line)) {
        istringstream iss(line);

        iss >> info;

        g->findVertex(info)->vertexSet(RESIDENCE);


    }
}

void GraphImporter::importBusStops(Graph<unsigned > *g, ifstream &BusStopsFile) {
    string line;
    unsigned info;

    while (getline(BusStopsFile, line)) {
        istringstream iss(line);

        iss >> info;

        g->findVertex(info)->vertexSet(BUSSTOP);
        //cout << info;
    }
}

void GraphImporter::importG_C(Graph<unsigned > *g, ifstream &G_CFile) {
    string line;
    unsigned info,s,d;
    double x, y , z;
    char c;
    int i=0;

    while (getline(G_CFile, line)) {
        istringstream iss(line);



        if(i==1){
            iss >> info;
            g->findVertex(info)->vertexSet(GARAGE);
            i++;
        }
        else if(i == 0){
            iss >> info;
            g->findVertex(info)->vertexSet(COMPANY);
            i =1;
        }
        else if(i == 2){
            iss >>c>> info >>c >> x >>c >> y >>c;

            cout << info<< " " << x<< " " << y<< endl;
            g->addVertex(info,x,y);
            g->findVertex(info)->vertexSet(DEAD);
            i++;
        }
        else{
            iss >>c >> s >>c >> d >>c;


            g->addEdge(s,d,0);
            g->addEdge(d,s,0);
        }


    }
}
