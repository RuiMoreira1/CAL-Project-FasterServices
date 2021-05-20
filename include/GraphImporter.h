

#ifndef CAL_PROJETCT_FASTERSERVICES_GRAPHIMPORTER_H
#define CAL_PROJETCT_FASTERSERVICES_GRAPHIMPORTER_H

#include <exception>
#include <string>

#include "Graph.h"

using namespace std;

class GraphImporter{
    private:

    void importNodes(Graph *g,ifstream &nodes_file);
    void importEdges(Graph *g,ifstream &edges_file);
};

#endif //CAL_PROJETCT_FASTERSERVICES_GRAPHIMPORTER_H
