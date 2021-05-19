#pragma once
#include <iostream>
#include "vector"
#include "Vehicle.h"



class Garage {
private:
    std::string address;
    std::vector<Vehicle> vehicles;
public:
    std::string getAddress() const;

    std::vector<Vehicle> getVehicles() const;

    friend std::ostream &operator<<( std::ostream &os, const Garage &garage );
};


