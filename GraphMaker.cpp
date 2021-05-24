#include <string>
#include <utility>

#include "GraphMaker.h"

GraphMaker::GraphMaker()  {
    display(600,600);

}

void GraphMaker::display(const unsigned int &width, const unsigned int &height) {
    gv.setCenter(sf::Vector2f(300, 300));
    gv.createWindow(width,height);


}

void GraphMaker::draw(const Graph<unsigned int> *g) {
    for (Vertex<unsigned> *v : g->getVertexSet()) {
        gv.addNode(v->getInfo(), sf::Vector2f(v->getPosition()->getLongitude(), v->getPosition()->getLatitude()) );
        //if (this->VertTag)
          //  gv.setVertexLabel(v->getInfo(), to_string(v->getInfo()));
    }

    for (Vertex<unsigned> *v : g->getVertexSet()) {
        for (Edge<unsigned> *e : v->getAdj())
            gv.addEdge(e->getEdgeId(), gv.getNode(v->getInfo()) , gv.getNode(e->getDest()->getInfo()),GraphViewer::Edge::EdgeType::UNDIRECTED);
    }
    gv.join();
}

