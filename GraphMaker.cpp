#include <string>
#include <utility>

#include "GraphMaker.h"

GraphMaker::GraphMaker()  {
    display(1000,1000);

}

void GraphMaker::display(const unsigned int &width, const unsigned int &height) {
    gv.setCenter(sf::Vector2f(500, 500));
    gv.createWindow(width,height);


}

void GraphMaker::draw(const Graph<unsigned int> *g) {
    for (Vertex<unsigned> *v : g->getVertexSet()) {
        GraphViewer::Node &node0 = gv.addNode(v->getInfo(), sf::Vector2f(v->getPosition()->getLongitude(), v->getPosition()->getLatitude()) );
        if(v->getVertexType() == RESIDENCE){
            node0.setColor(GraphViewer::BLUE);
        }
        else if(v->getVertexType() == COMPANY){
            node0.setColor(GraphViewer::YELLOW);
        }
        else if(v->getVertexType() == GARAGE){
            node0.setColor(GraphViewer::GREEN);
        }
        //if (this->VertTag)
          //  gv.setVertexLabel(v->getInfo(), to_string(v->getInfo()));
    }

    for (Vertex<unsigned> *v : g->getVertexSet()) {
        for (Edge<unsigned> *e : v->getAdj())
            gv.addEdge(e->getEdgeId(), gv.getNode(v->getInfo()) , gv.getNode(e->getDest()->getInfo()),GraphViewer::Edge::EdgeType::UNDIRECTED);
    }

}

void GraphMaker::routeDraw(const Graph<unsigned> *g,
                              vector<unsigned> vertex_path) {

    if (vertex_path.size() <= 1)
        throw;

    Vertex<unsigned> *start = g->findVertex(vertex_path.at(0));
    if (start == nullptr)
        throw;

    size_t i = 0;
    for (auto it = vertex_path.begin() + 1; it != vertex_path.end(); ++it) {
        for (Edge<unsigned> *edge : start->getAdj()) {
            if (edge->getDest()->getInfo() == *it) {
                cout << *it;
                int edgeId = edge->getEdgeId();
                GraphViewer::Edge e1 = gv.getEdge(edgeId);
                e1.setColor(GraphViewer::BLUE);
                start = edge->getDest();
                break;
            }
        }
    }
}

void GraphMaker::view() {
    gv.join();
}

