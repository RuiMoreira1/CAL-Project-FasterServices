#pragma once
#include <iostream>
#include "vector"
#include "Worker.h"


class Client {
private:
    int Id;
    std::vector<Worker> workers;
    std::string Adress;

public:
    int getId() const;

    bool operator==(const Client &client) const;

    bool operator!=(const Client &client) const;
};


