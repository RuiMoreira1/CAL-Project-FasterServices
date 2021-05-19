#pragma once


#include <iostream>
#include <math.h>

using namespace std;

class Position {
    double latitude, longitude;
public:
    Position(double latitude, double longitude);
    Position() = default;

    double getLatitude() const;
    double getLongitude() const;

    double distanceBetweenPositions(const Position &position);

    bool operator==(const Position &position) const;

    bool operator!=(const Position &position) const;

    friend ostream &operator<<(ostream &os, const Position &position);
};



