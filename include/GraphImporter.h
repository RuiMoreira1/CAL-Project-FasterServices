

#ifndef CAL_PROJETCT_FASTERSERVICES_GRAPHIMPORTER_H
#define CAL_PROJETCT_FASTERSERVICES_GRAPHIMPORTER_H

#include <exception>
#include <string>

#include "Graph.h"

using namespace std;

class GraphImporter{
    private:

    void importNodes(Graph<unsigned > *g,ifstream &NodesFile);
    void importEdges(Graph<unsigned > *g,ifstream &EdgesFile);

public:
    GraphImporter();

    Graph<unsigned> *importAll(const string NodesFile,const string EdgesFile);

    vector<Vertex<unsigned> *> importCompany(Graph<unsigned> *g,const string &CompanyFile) const;
};

#endif //CAL_PROJETCT_FASTERSERVICES_GRAPHIMPORTER_H
