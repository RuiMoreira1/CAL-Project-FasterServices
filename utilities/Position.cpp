#include "Position.h"

double Position::getLatitude() const {
    return latitude;
}

double Position::getLongitude() const {
    return longitude;
}

double Position::distanceBetweenPositions(const Position &position) {
    return sqrt(pow(this->latitude - position.getLatitude(),2)+pow(this->getLongitude() - position.getLongitude(),2));
}

bool Position::operator==(const Position &position) const {
    return this->latitude == position.getLatitude() && this->longitude == position.getLongitude();
}

bool Position::operator!=(const Position &position) const {
    return !(position == *this);
}

ostream &operator<<(ostream &os, const Position &position){
    os << "(" << position.getLatitude() << ", " << position.getLongitude() << ")\n";
    return os;
}
