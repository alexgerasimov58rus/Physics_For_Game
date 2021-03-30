
#pragma once

#include "../tools_exp.hpp"
#include "../Vector/Vector2D.hpp"
#include "../Vector/Vector3D.hpp"
#include <vector>
#include <string>

namespace obj_tools {

	struct OBJ_TOOLS_EXPORT Mesh
	{
		Mesh(const std::string& name);
	   ~Mesh(void);

		bool loadFromObjFile(const std::string& path);
		void compile(void);
		void render(void) const;

		double getBoundingSphereRadius(void) const { return this->boundingSphereRadius_; }

		std::string getName(void) const { return this->name_; }

		private: //_____________________________

		struct Face {
			Face(void) {
				memset(this->indexes_[0], -1, 3);
				memset(this->indexes_[1], -1, 3);
				memset(this->indexes_[2], -1, 3);
			}

			bool isValid(int i, int j) const {
				i = (i > 2) ? 2 : i;
				i = (i < 0) ? 0 : i;
				j = (j > 2) ? 2 : j;
				j = (j < 0) ? 0 : j;

				return indexes_[i][j] >= 0;
			}

			size_t indexes_[3][3];
		};

		void clear(void);
		void deleteCallList(void);

		bool addVertex(const std::string& line);
		bool addTexel (const std::string& line);
		bool addNormal(const std::string& line);
		bool addFace  (const std::string& line);

		bool parseFaceWithSeparator(int* indexes, const std::string& s) const;
		bool parseFaceWithoutSeparator(int* indexes, const std::string& s) const;

		void calcGeometryCenter(void);
		void calcBoundingRadius(void);

		std::string name_;

		std::vector<Vector3D> vertices_;
		std::vector<Vector3D> normals_;
		std::vector<Vector2D> texels_;

		std::vector<Face> faces_;

		Vector3D geometryCenter_;
		double	 boundingSphereRadius_;

		size_t callIndex_;
	};
};