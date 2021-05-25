#include "MeetingPoint.h"

#include "include/MeetingPoint.h"

bool MeetingPoint::operator<(const MeetingPoint &mp) const {
    return this->assigned_workers.size() >= mp.assigned_workers.size();;
}

bool MeetingPoint::operator==(const MeetingPoint &mp) const {
    return mp.v == this->v;
}

void MeetingPoint::addWorker(Vertex<unsigned>* w) {
    this->assigned_workers.insert(w);
}

bool MeetingPoint::removeWorker(Vertex<unsigned>* w) {
    if (this->assigned_workers.find(w) == this->assigned_workers.end())
        return false;

    this->assigned_workers.erase(w);
    return true;
}

bool MeetingPoint::isProcessed() const {
    return this->processed;
}

void MeetingPoint::setProcessed(bool processed) {
    this->processed = processed;
}

set<Vertex<unsigned>*> MeetingPoint::getWorkers() const {
    return this->assigned_workers;
}


