
#include "Math.hpp"
#include <math.h>

using namespace obj_tools;
using namespace std;

#define DELTA 0.000001

const double Math::PI = 3.141592653589;
const double Math::G = 9.8;

bool Math::isCloseToZero(const float& value) {
    return fabs(value) <= DELTA;
}

double Math::degToRad(const double& deg) {
    return deg * PI / 180.0;
}

double Math::getInertiaMomentHomogeneousSphere(const float& r, const float& m) {
    return 2 * (double)m * r * r / 5.0;
}

double Math::getInertiaMomentHollowSphere(const float& r, const float& m) {
    return 2 * (double)m * r * r / 3.0;
}

double Math::getInertiaMomentHoopRelativeAxis(const float& r, const float& m) {
    return (double)m * r * r;
}

double Math::getInertiaMomentHoopRelativeDiameter(const float& r, const float& m) {
    return (double)m * r * r / 2.0;
}

double Math::getInertiaMomentHoopRelativeTangent(const float& r, const float& m) {
    return 3 * (double)m * r * r / 2.0;
}

double Math::getInertiaMomentCylinderRelativeAxis(const float& r, const float& m) {
    return (double)m * r * r / 2.0;
}

double Math::getInertiaMomentCylinderRelativeDiameter(const float& r, const float& l, const float& m) {
    return (double)m * r * r / 4.0 + (double)m * l * l / 12.0;
}