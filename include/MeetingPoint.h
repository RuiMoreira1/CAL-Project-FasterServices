#pragma once
#include <set>

#include "Graph.h"

class MeetingPoint {
private:
    Vertex<unsigned> *v;
    set<Vertex<unsigned> *> assigned_workers;
    int queueIndex = 0; // required by MutablePriorityQueue
    bool processed = false;

public:
    MeetingPoint(Vertex<unsigned> *v) { this->v = v; }
    bool
    operator<(const MeetingPoint &mp) const; // required by MutablePriorityQueue
    /**
     * 2 MeetingPoints are equal if the info of their Vertexes is equal.
     */
    bool operator==(const MeetingPoint &mp) const;
    /**
     * 2 MeetingPoints are different if the info of their Vertexes is different.
     */
    bool operator!=(const MeetingPoint &mp) const { return !(*this == mp); }

    // Getters and Setters
    set<Vertex<unsigned> *> getWorkers() const;
    /**
     * Add a Vertex that represents the residence of a worker to this MeetingPoint.
     */
    void addWorker(Vertex<unsigned> *w);
    /**
     * Remove a Vertex that represents the residence of a worker to this MeetingPoint.
     */
    bool removeWorker(Vertex<unsigned> *w);
    bool isProcessed() const;
    void setProcessed(bool processed);
    /**
     * Get info of the Vertex that the MeetingPoint contains.
     */
    unsigned getInfo() const { return v->getInfo(); }
    /**
     * Get the Vertex that the MeetingPoint contains.
     */
    Vertex<unsigned> *getVertex() const { return this->v; }

    friend class MutablePriorityQueue<MeetingPoint>;
};


