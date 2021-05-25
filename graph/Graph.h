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


#define LARGEST std::numeric_limits<double>::max()
#define SMALLER std::numeric_limits<double>::min()

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
    DEAD
};

template <class T> class Vertex {
private:
    T info; // contents

    bool visited = false;    // auxiliary field

    bool bidirectionVisited = false;

    VertexType vType;

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

    /**
     * @brief Get the vertex information
     * @return Class vertex info parameter.
     */
    T getInfo() const { return this->info; }

    /**
     * @brief Get the dist of this vertex
     * @return The Vertex Class dist parameter.
     */
    double getDist() const { return this->dist; }

    /**
     * @brief Get a pointer to the previous Vertex on the path calculated.
     * @return NULL pointer if the current Vertex is the origin of the calculated path, otherwise return the previous
     *         the previous vertex in the path
     */
    Vertex *getPath() const { return this->path; }

    /**
     * @brief Get the vector of outgoing adjacent edges of this Vertex.
     * @return The list of outgoing adjacent edges of this Vertex
     */
    vector<Edge<T> *> getAdj() const { return this->adj; }

    /**
     * @brief Get the vector of incoming adjacent edges of this Vertex.
     * @return The list of incoming adjacent edges of this Vertex.
     */
    vector<Edge<T> *> getInc() const { return this->inc; }

    /**
     * @brief Setter function to modifie the current Vertex position
     * @param pos - Position class pointer object, with the new Vertex position
     */
    void setPosition(Position *pos) { this->position = position; }

    /**
     * @brief Getter function to get the current Vertex Position*
     * @return Current Vertex Position*
     */
    Position* getPosition() const { return this->position; }

    /**
     * @brief Set the vertexType enum to a specified type
     * @param vertexType - VertexType enum
     */
    void vertexSet( VertexType vertexType ) { this->vType = vertexType; }

    /**
     * @brief Getter function to get the VertexType
     * @return Current VertexType
     */
    VertexType getVertexType() const { return this->vType; }

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

    Vertex<T> *getDest() const { return this->dest; }

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
    /**
     * @brief Checks and edge using single source shortest path algorithm
     * @returns true if the vertex was indeed relaxed
     */
    bool relax(Vertex<T> *v, Vertex<T> *w, double weight);

    /**
     * @brief Receives the content of a source vertex and returns a pointer
     * the source vertex
     */
    bool initBidirectionalDijkstra(const T &source, const T &destination, Vertex<T> *&src, Vertex<T> *&dest);

    /**
     * @brief After running the bidirection dijkstra algorithm, call this function to clean the path calculated
     *        by the algorithm
     */
    bool dijkstraBidirectionalFixPath(Vertex<T> *midPoint, Vertex<T> *nextDest, double weight);

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

    bool dijkstraShortestPath(const T &source);

    bool dijkstraShortestPath(const T &source, const T &destination);

    bool dijkstraBidirectional(const T &source, const T &destination);

    vector<T> getPath(const T &source, const T &destination) const;

    vector<T> getPath(const T &source, const T &destination, double *distance) const;

    vector<Vertex<T> *>DFS(T const source) const;

    Graph<T> * genInvertedGraph(vector<Vertex<unsigned int> *> vertexes) const;

    void clearEmptyVert(void);

    ~Graph();

};

template<class T>
vector<T> Graph<T>::getPath(const T &source, const T &destination, double *distance) const {
    *distance = LARGEST;

    vector<T> result;

    Vertex<T> * destinationVertex = findVertex(destination);
    Vertex<T> * sourceVertex = findVertex(source);

    if( sourceVertex == nullptr || destinationVertex == nullptr || destinationVertex->dist == LARGEST || destinationVertex->info == sourceVertex->info )
        return result;

    *distance = destinationVertex->dist;
    /*
    while( destinationVertex != NULL ){
        destinationVertex = destinationVertex->path;
        result.push_back(destinationVertex->info);
        if( destinationVertex->info == sourceVertex->info ) break;
    }*/

    for(; destinationVertex != nullptr; destinationVertex = destinationVertex->path){
        result.push_back(destinationVertex->info);
        if( destinationVertex->info == sourceVertex->info ) break;
    }

    reverse(result.begin(),result.end());

    return result;
}

template <class T>
inline bool Graph<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
    if (v->dist + weight < w->dist) {
        w->dist = v->dist + weight;
        w->path = v;
        return true;
    }
    return false;
}

template <class T>
bool Graph<T>::initBidirectionalDijkstra(const T &source, const T &destination, Vertex<T> *&src, Vertex<T> *&dest) {
    for (auto v : vertexSet) {
        v->dist = LARGEST;
        v->visited = false;
        v->bidirectionVisited = false;
        v->path = nullptr;}

        src = findVertex(source);
    if (src == nullptr) {
        cout << "Failed to find origin\n";
        return false;
    }

    dest = findVertex(destination);
    if (dest == nullptr) {
        cout << "Failed to find destination\n";
        return false;
    }

    src->dist = 0;
    dest->dist = 0;
    return true;
}

template <class T>
bool Graph<T>::dijkstraBidirectionalFixPath(Vertex<T> *midPoint, Vertex<T> *nextDest, double weight) {
    double oldDist;
    double w = weight;
    Vertex<T> *next = nextDest->path;

    do {
        oldDist = nextDest->dist;
        nextDest->dist = midPoint->dist + w;
        next = nextDest->path;
        nextDest->path = midPoint;

        midPoint = nextDest;
        nextDest = next;
        if (nextDest != nullptr)
            w = oldDist - nextDest->dist;
    } while (next != nullptr);

    return true;
}

template<class T>
bool Graph<T>::dijkstraBidirectional(const T &source, const T &destination) {
    Vertex<T> *src = nullptr, *dest = nullptr;

    if (!initBidirectionalDijkstra(source, destination, src, dest)) {
        cout << "Failed Here\n";
        return false;
    }

    // if (origin == dest)
    // return true;

    MutablePriorityQueue<Vertex<T>> srcPq;
    srcPq.insert(src);
    MutablePriorityQueue<Vertex<T>> destPq;
    destPq.insert(dest);

    Vertex<T> *srcTop = nullptr, *destTop = nullptr;
    while (!srcPq.empty() && !destPq.empty()) {
        srcTop = srcPq.extractMin();
        srcTop->visited = true;
        for (Edge<T> *e : srcTop->adj) {
            if (e->dest->bidirectionVisited) { // Found path
                return dijkstraBidirectionalFixPath(srcTop, e->dest, e->weight);
            }
            if (relax(srcTop, e->dest, e->weight)) {
                if (!e->dest->visited) {
                    srcPq.insert(e->dest);
                    e->dest->visited = true;
                } else
                    srcPq.decreaseKey(e->dest);
            }
        }

        destTop = destPq.extractMin();
        destTop->bidirectionVisited = true;
        for (Edge<T> *edge : destTop->inc) {
            if (edge->orig->visited) { // Found path
                return dijkstraBidirectionalFixPath(edge->orig, destTop, edge->weight);
            }
            if (relax(destTop, edge->orig, edge->weight)) {
                if (!edge->orig->bidirectionVisited) {
                    destPq.insert(edge->orig);
                    edge->orig->bidirectionVisited = true;
                } else
                    destPq.decreaseKey(edge->orig);
            }
        }

    }
    cout << "Failed Here2\n";
    return false;
}


template<class T>
Vertex<T>* Graph<T>::findVertex(const T &in) const {
    for(auto v: vertexSet){
        if(v->info == in){
            return v;
        }
    }
    return nullptr;
}


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

template <class T> void Vertex<T>::addEdge(Vertex<T> *d, double w, int edgeId) {
    Edge<T> *e = new Edge<T>(this, d, w, edgeId);
    adj.push_back(e);
    d->inc.push_back(e);
}

template<class T> Graph<T>::~Graph() {
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

template <class T> vector<Vertex<T> *> Graph<T>::DFS(T const source) const {
    vector<Vertex<T> *> res;

    Vertex<T> *s = findVertex(source);
    if (s == nullptr)
        return res;

    for (Vertex<T> *v : vertexSet)
        v->visited = false;

    stack<Vertex<T> *> stack;
    stack.push(s);
    while (!stack.empty()) {
        auto v = stack.top();
        stack.pop();

        if (!v->visited) {
            res.push_back(v);
            v->visited = true;
        }

        for (Edge<T> *e : v->adj) {
            if (!e->dest->visited)
                stack.push(e->dest);
        }
    }

    return res;
}

template <class T>
Graph<T> *Graph<T>::genInvertedGraph(vector<Vertex<unsigned int> *> vertexes) const {
    Graph<T> *invertedG = new Graph<T>;

    for (Vertex<T> *v : vertexes) {
        invertedG->addVertex(v->info, *v->position);
        cout << v->getInfo() << endl;
    }

    for (Vertex<T> *v : vertexes) {
        for (Edge<T> *e : v->adj) {
            if (invertedG->findVertex(e->getDest()->info) != nullptr)
                invertedG->addEdge(e->getDest()->info, v->info, e->getWeight());
        }
    }

    return invertedG;
}

template <class T> void Graph<T>::clearEmptyVert(void) {
    for (auto it = vertexSet.begin(); it!=vertexSet.end();) {
        if ((*it)->adj.empty() && (*it)->inc.empty()) {
            delete (*it);
            it = vertexSet.erase(it);
        }
        else
            ++it;
    }
}







#endif




