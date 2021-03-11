#include "pch.h"
#include "CppUnitTest.h"
#include "../../src/obj_tools.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace obj_tools;

namespace unittests
{
	TEST_CLASS(Vector3d)
	{
	public:

		TEST_METHOD(TestConstructors)
		{
			Vector3D v1;
			Assert::AreEqual(v1.getX(), 0.0f);
			Assert::AreEqual(v1.getY(), 0.0f);
			Assert::AreEqual(v1.getZ(), 0.0f);

			Vector3D v2(2.0f, 3.0f, 4.0f);
			Assert::AreEqual(v2.getX(), 2.0f);
			Assert::AreEqual(v2.getY(), 3.0f);
			Assert::AreEqual(v2.getZ(), 4.0f);

			Vector3D v3(v2);
			Assert::AreEqual(v3.getX(), 2.0f);
			Assert::AreEqual(v3.getY(), 3.0f);
			Assert::AreEqual(v3.getZ(), 4.0f);
		}

		TEST_METHOD(TestAdditionOperators)
		{
			Vector3D rs(3, 5, 8);

			Vector3D v1(2, 3, 4);
			Vector3D v2(1, 2, 4);
			Vector3D v3 = v1 + v2;
			Assert::IsTrue(v3 == rs);

			v2 += v1;
			Assert::IsTrue(v2 == rs);
		}

		TEST_METHOD(TestSubstractionOperators)
		{
			Vector3D rs(2, 3, 4);
			Vector3D v1(3, 5, 8);
			Vector3D v2(1, 2, 4);
			Vector3D v3 = v1 - v2;
			Assert::IsTrue(v3 == rs);

			v1 -= v2;
			Assert::IsTrue(v1 == rs);
		}

		TEST_METHOD(TestMultiplyOperators)
		{
			Vector3D rs(4, 6, 8);
			Vector3D v1(2, 3, 4);
			Vector3D v2 = v1 * 2.0f;
			Assert::IsTrue(v2 == rs);

			Vector3D v3 = 2.0f * v1;
			Assert::IsTrue(v3 == rs);

			v1 *= 2.0;
			Assert::IsTrue(v1 == rs);
		}

		TEST_METHOD(TestDot)
		{
			Vector3D v1(2, 3, 4);
			Vector3D v2(1, 2, 3);

			Assert::AreEqual(v1.dot(v2), 2 * 1.0 + 3 * 2.0 + 4 * 3.0);
		}

		TEST_METHOD(TestNorm)
		{
			Vector3D v1(4, 5, 6);

			Assert::AreEqual(v1.normSquared(), 4.0 * 4.0 + 5.0 * 5.0 + 6.0 * 6.0);
			Assert::AreEqual(v1.norm(), sqrt(v1.normSquared()));
		}

		TEST_METHOD(TestNormalize)
		{
			Vector3D v1(4, 5, 6);
			Vector3D v2(
				(float)(4 / v1.norm()), 
				(float)(5 / v1.norm()), 
				(float)(6 / v1.norm()));

			Assert::IsTrue(fabs(v1.normalize(1e-6).getX() - v2.getX()) < 1e-6);
			Assert::IsTrue(fabs(v1.normalize(1e-6).getY() - v2.getY()) < 1e-6);
			Assert::IsTrue(fabs(v1.normalize(1e-6).getZ() - v2.getZ()) < 1e-6);
		}

		TEST_METHOD(TestCross)
		{
			Vector3D rs(-10, 5, 0);

			Vector3D v1(1, 2, 3);
			Vector3D v2(4, 8, 7);

			Vector3D v3 = v1.cross(v2);

			Assert::IsTrue(v1.cross(v2) == rs);
		}

		TEST_METHOD(TestFloor)
		{
			Vector3D v1(4.12345f, 5.23456f, 6.65433f);
			Vector3D rs(4.123f, 5.234f, 6.654f);

			Assert::IsTrue(v1.floor(3) == rs);
		}
	};
};