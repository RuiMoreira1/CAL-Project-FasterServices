#include "client.h"


int Client::getId() const {
    return this->Id;
}

bool Client::operator==( const Client &client) const {
    return Id == client.getId();
}

bool Client::operator!=( const Client &client) const {
    return !(client == *this);
}
