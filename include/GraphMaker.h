

#ifndef CAL_PROJETCT_FASTERSERVICES_GRAPHMAKER_H
#define CAL_PROJETCT_FASTERSERVICES_GRAPHMAKER_H

#include "graphviewer.h"
#include "Graph.h"

class GraphMaker {
private:
    GraphViewer gv;

    void display(const unsigned &width, const unsigned &height);

    bool VertTag = false;

public:

    GraphMaker();

    void setVertTag(bool tag){VertTag = tag;}

    void close();

    void draw(const Graph<unsigned > *g);

};

#endif //CAL_PROJETCT_FASTERSERVICES_GRAPHMAKER_H
