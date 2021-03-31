
#pragma once
#include "../tools_exp.hpp"

namespace obj_tools {
    struct OBJ_TOOLS_EXPORT Math
    {
        static const double PI;
        static double degToRad(const double& deg);

        static double getInertiaMomentHomogeneousSphere(const float& r, const float& m);
        static double getInertiaMomentHollowSphere(const float& r, const float& m);
        static double getInertiaMomentHoopRelativeAxis(const float& r, const float& m);
        static double getInertiaMomentHoopRelativeDiameter(const float& r, const float& m);
        static double getInertiaMomentHoopRelativeTangent(const float& r, const float& m);
        static double getInertiaMomentCylinderRelativeAxis(const float& r, const float& m);
        static double getInertiaMomentCylinderRelativeDiameter(const float& r, const float& l, const float& m);
    };
};