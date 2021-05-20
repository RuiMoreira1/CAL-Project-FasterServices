#include "Worker.h"

/**
 * @brief Getter function
 * @return Worker name
 */
std::string Worker::getName() const {
    return this->name;
}

/**
 * @brief Getter function
 * @return Worker address
 */
std::string Worker::getAddress() const {
    return this->address;
}

/**
 * @brief Getter function
 * @return Worker id
 */
int Worker::getId() const {
    return this->id;
}

/**
 * @brief Worker class operator==
 * @return true if we are talking about the same worker
 */
bool Worker::operator==(const Worker &worker) {
    return this->id == worker.getId() && this->name == worker.getName() && this->address == worker.getAddress();
}

/**
 * @brief Worker class operator!=
 * @return false if we are talking about the same worker
 */
bool Worker::operator!=(const Worker &worker) {
    return !( *this == worker );
}

/**
 * @brief Ostream operator to output text
 * @param os
 * @param worker
 * @return
 */
std::ostream &operator<<(std::ostream os, const Worker &worker) {
    os << worker.getAddress() << worker.getId();
    return os;
}
