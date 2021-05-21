
#pragma once

#include "../tools_exp.hpp"
#include <vector>

namespace obj_tools {

    struct PointMassBase;
    struct Spring;
    struct Vector3D;

	struct OBJ_TOOLS_EXPORT Cloth
	{
        Cloth(
            const int& particleRows,
            const int& particleCols,
            PointMassBase* particle,
            const float& spaceBetweenParticles,
            const float& clothStiffnes,
            const float& dampeningFactor,
            const float& lineardampeningFactor,
            const Vector3D upLeftCorner);

        void update(const float& dTime);
        void render(void);

        void applyImpulseForce(int row, int col, const Vector3D& force, const float& timeOfAction);


		private: //_____________________________

		enum CONSTANTS {
            PARTICLES_PER_SQUARE = 4,
            TOP_LEFT_PARTICLE = 0,
            TOP_RIGHT_PARTICLE,
            BOTTOM_LEFT_PARTICLE,
            BOTTOM_RIGHT_PARTICLE,
            TOP_SPRING = 0,
            BOTTOM_SPRING,
            RIGHT_SPRING,
            LEFT_SPRING,
            TOP_RIGHT_TO_BOTTOM_LEFT_SPRING,
            TOP_LEFT_TO_BOTTOM_RIGHT_SPRING,
            SPRINGS_PER_SQUARE = 6
		};

        struct index_pair{
            int row;
            int col;
        };

        struct cloth_square{
            index_pair particleIndex[PARTICLES_PER_SQUARE];
            int springIndex[SPRINGS_PER_SQUARE];
        };

        void handleCollision(
            Vector3D separationDistance,
            float changeInTime,
            index_pair firstParticle,
            index_pair secondParticle);

        int totalRows_;
        int totalCols_;
        int totalSprings_;

        std::vector< std::vector<PointMassBase*> > particles_;
        std::vector< Spring* > springs_;
        std::vector< std::vector<cloth_square> > squares_;

        float linearDampeningCoeff_;
	};
}