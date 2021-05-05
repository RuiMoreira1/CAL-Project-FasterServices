
#include <iostream>
#include "vector"
#include "Worker.h"
#ifndef CLIENT_H
#define CLIENT_H


class client {
    int Id;
    std::vector<Worker> workers;
    std::string Adress;

    public:
    int getId(){return this->Id;};
};


#endif
