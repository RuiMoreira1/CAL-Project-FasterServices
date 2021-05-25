#include <iostream>
#include "graph/Graph.h"
#include "GraphMaker.h"
#include "GraphImporter.h"
#include "Solver.h"

int main() {
    /*GraphViewer gv;                         // Instantiate GraphViewer
    gv.setCenter(sf::Vector2f(300, 300));   // Set coordinates of window center
    GraphViewer::Node &node0 = gv.addNode(0, sf::Vector2f(200, 300)); // Create node
    node0.setColor(GraphViewer::BLUE);
    GraphViewer::Node &node1 = gv.addNode(1, sf::Vector2f(400, 100));
    GraphViewer::Edge &edge1 =
            gv.addEdge(0,node0,node1,GraphViewer::Edge::EdgeType::UNDIRECTED);


    gv.createWindow(600, 600);     // Create window
    gv.join();                     // Join viewer thread (blocks till window closed)
    return 0;*/
    GraphMaker g1;
    GraphImporter *gM = new GraphImporter();
    Graph<unsigned > *graph = gM->importAll("../resources/maps/GridGraphs/8x8/nodes.txt","../resources/maps/GridGraphs/8x8/edges.txt",
                                      "../resources/maps/GridGraphs/workers","../resources/maps/GridGraphs/company_garage");
    //graph->addVertex(1,200,200);
    //graph->addVertex(2,324,435);
    //graph->addEdge(1,2);



    Graph<unsigned > graph1 = *graph;
    Solver *s1 = new Solver(graph);
    vector<unsigned> path = s1->tsp();
    for( auto v: path){
        cout << v << endl;
    }
    g1.draw(graph);
    //g1.routeDraw(graph,path);
    g1.view();

}
