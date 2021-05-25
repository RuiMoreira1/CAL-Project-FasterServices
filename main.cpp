#include <iostream>
#include "graph/Graph.h"
#include "GraphMaker.h"
#include "GraphImporter.h"
#include "Solver.h"

int main() {

    //EXEMPLO GRIDGRAPH 8x8
    GraphMaker g1;
    GraphImporter *gM = new GraphImporter();
    Graph<unsigned > *graph = gM->importAll("../resources/maps/GridGraphs/8x8/nodes.txt","../resources/maps/GridGraphs/8x8/edges.txt",
                                      "../resources/maps/GridGraphs/workers","../resources/maps/GridGraphs/company_garage");


    Graph<unsigned > graph1 = *graph;
    Solver *s1 = new Solver(graph);
    vector<unsigned> path = s1->tsp();

    g1.draw(graph);
    g1.routeDraw(graph,path);
    g1.view();

}
