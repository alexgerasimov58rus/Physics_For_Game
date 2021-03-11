
#include "Math.hpp"

using namespace obj_tools;

const double Math::PI = 3.141592653589;

double Math::degToRad(const double& deg) {
    return deg * PI / 180.0;
}

