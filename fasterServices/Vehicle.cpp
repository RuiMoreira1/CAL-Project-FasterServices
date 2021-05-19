#include "Vehicle.h"

std::string Vehicle::getName() const {
    return this->name;
}

int Vehicle::getId() const {
    return this->id;
}

int Vehicle::getCapacity() const {
    return this->capacity;
}

Client* Vehicle::getClient() {
    return this->client;
}

std::vector<Worker*> Vehicle::getWorkers() {
    return this->workers;
}

bool Vehicle::operator==(const Vehicle &vehicle) const {
    return (vehicle.getId() == id);
}

bool Vehicle::operator!=(const Vehicle &vehicle) const {
    return !( vehicle == *this );
}

std::ostream &operator<<(std::ostream os, const Vehicle &vehicle) {
    os << "Vehicle ->" << vehicle.getName() << " | Id: " << vehicle.getId() << "\n";
    return os;
}
