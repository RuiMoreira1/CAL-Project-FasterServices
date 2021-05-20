

#ifndef CAL_PROJETCT_FASTERSERVICES_GRAPHMAKER_H
#define CAL_PROJETCT_FASTERSERVICES_GRAPHMAKER_H

#include "graphviewer.h"
#include "Graph.h"

class GraphRenderer {
private:
    GraphViewer gv;

    GraphViewer createViewer(bool is_interactive, char const *const vertex_color,
                             char const *const edge_color) const;

    void display(const unsigned &width, const unsigned &height);

    bool VertTag = false;

public:

    GraphRenderer();

    void setVertTag(bool tag){VertTag = tag;}

    void close();

    void draw(const Graph *g);

};

#endif //CAL_PROJETCT_FASTERSERVICES_GRAPHMAKER_H
