#include "Graph.h"

template<class T>
bool Vertex<T>::operator<(Vertex<T> &vertex) const {
    return this->dist < vertex.getDist();
}

template<class T>
void Vertex<T>::addEdge(Edge <T> *edge, double weigth, int edgeID) {
    Edge<T> *e = new Edge<T>(this, edge, weigth, edgeID);
    adj.push_back(e);
    edge->inc.push_back(e);
}



template<class T>
Graph<T>::~Graph() {
    for (Vertex<T> *v : this->vertexSet) {
        for (Edge<T> *e : v->adj){ delete e; }
        delete v;
    }
}

template <class T> bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

template <class T> bool Graph<T>::addVertex(const T &in, double x, double y) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex<T>(in, x, y));
    return true;
}

template <class T> bool Graph<T>::addVertex(const T &in,  Position &position) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex<T>(in, position));
    return true;
}

template <class T> bool Graph<T>::addEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;

    double w = v1->coord.dist(v2->coord);
    return addEdge(v1, v2, w);
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    return addEdge(v1, v2, w);
}

template <class T>
bool Graph<T>::addEdge(Vertex<T> *v1, Vertex<T> *v2, double w) {
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, ++edgeIdCounter);
    return true;
}

