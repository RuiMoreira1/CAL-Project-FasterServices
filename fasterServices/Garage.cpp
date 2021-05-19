#include "Garage.h"


std::string Garage::getAddress() const {
    return this->address;
}

std::vector<Vehicle> Garage::getVehicles() const {
    return this->vehicles;
}

std::ostream &operator<<(std::ostream &os, const Garage &garage) {
    os << "Garage adress -> " << garage.getAddress() << "\n Vehicles owned by the garage:\n";
    for( Vehicle &vehicle : garage.getVehicles() ){
        os << "Vehicle ->" << vehicle.getName() << " | Id: " << vehicle.getId() << "\n";
    }
    return os;
}




