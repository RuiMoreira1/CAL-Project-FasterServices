#pragma once
#include <iostream>
#include <string>

/**
 * @class Worker
 * @brief Worker class, used to manage the workers
 * @param name - Worker name
 * @param address - Worker address
 * @param id - Worker id
 */
class Worker {
private:
    std::string name;
    int id;
    std::string address;
public:
    std::string getName() const;
    std::string getAddress() const;

    int getId() const;

    bool operator==(const Worker &worker);

    bool operator!=(const Worker &worker);

    friend std::ostream &operator<< ( std::ostream os, const Worker &worker);
};


