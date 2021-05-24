#pragma once

#ifndef CAL_PROJETCT_FASTERSERVICES_GRAPH_H
#define CAL_PROJETCT_FASTERSERVICES_GRAPH_H
#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include "Position.h"
#include "MutablePriorityQueue.h"


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

/* ================================================================================================
 * Class Vertex
 * ================================================================================================
 */

//This enum might be important to use to enumerate each vertex
enum VertexType {
    // NORMAL_VERTEX Set empty => Normal Vertex
    BUSSTOP,
    RESIDENCE,
    COMPANY,
    GARAGE,
    OBSTRUCTION,
    MEETINGPOINT,
};

template <class T> class Vertex {
private:
    T info; // contents

    bool visited = false;    // auxiliary field


    double dist = 0;
    Vertex<T> *path = nullptr;
    vector<Edge<T> *> adj; // outgoing edges
    vector<Edge<T> *> inc; // incoming edges
    int queueIndex = 0;    // required by MutablePriorityQueue
    void addEdge(Vertex<T> *dest, double w, int edgeId);

    Position *position;

    //Might be necessary to move to the public side
    bool operator<(Vertex<T> &vertex) const; // required by MutablePriorityQueue

    void addEdge(Edge<T> *edge, double weigth, int edgeID);

public:
    Vertex(T in) : info(in), position( new Position() ) {}
    Vertex(T in, double x, double y) : info(in), position( new Position(x,y) ) {}
    Vertex(T in, Position coord) : info(in), position( new Position(coord) ) {}

    T getInfo() const { return this->info; }

    double getDist() const { return this->dist; }

    Vertex *getPath() const { return this->path; }

    vector<Edge<T> *> getAdj(void) const { return this->adj; }

    vector<Edge<T> *> getInc(void) const { return this->inc; }

    void setCoords(Position *pos) { this->position = position; }

    Position* getPosition() const { return this->position; }

    //bool operator<(Vertex<T> &vertex) const; // required by MutablePriorityQueue

    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};

/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */

template <class T> class Edge {
    Vertex<T> *orig;
    Vertex<T> *dest;
    double weight;
    int edgeId;


public:
    Edge(Vertex<T> *o, Vertex<T> *d, double w, unsigned edgeId) : orig(o), dest(d), weight(w), edgeId(edgeId) {}

    double getWeight() const { return weight; }

    Vertex<T> *getDest(void) const { return this->dest; }

    int getEdgeId() const { return this->edgeId; }

    friend class Graph<T>;
    friend class Vertex<T>;
};


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */

template <class T> class Graph {
    int edgeIdCounter = 0;
    vector<Vertex<T> *> vertexSet;

public:
    vector<Vertex<T> *> getVertexSet() const { return vertexSet; }

    Vertex<T> *findVertex(const T &in) const;
    Vertex<T> *findVertex(const Position &position) const;
    bool addVertex(const T &in);
    bool addVertex(const T &in, double x, double y);
    bool addVertex(const T &in, Position &position);
    bool addVertexInOrder(const T &in, Position &position);

    bool addEdge(const T &sourc, const T &dest);
    bool addEdge(const T &sourc, const T &dest, double w);
    bool addEdge(Vertex<T> *v1, Vertex<T> *v2, double w);
    bool addEdgeInOrder(const T &sourc, const T &dest, double w);
    ~Graph();

};

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


template <class T> bool Graph<T>::addEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;

    double w = v1->position->distanceBetweenPositions(*v2->position);
    return addEdge(v1, v2, w);
}







#endif




