#pragma once
#include <iostream>
#include "client.h"


class Vehicle {
private:
    std::string name;
    int id;
    int capacity;
    Client *client;
    std::vector<Worker*> workers;
public:
    std::string getName() const;

    int getId() const;
    int getCapacity() const;

    Client* getClient();

    std::vector<Worker*> getWorkers();

    bool operator==(const Vehicle &vehicle) const;

    bool operator!=(const Vehicle &vehicle) const;

    friend std::ostream &operator<<(std::ostream os, const Vehicle &vehicle);

};

