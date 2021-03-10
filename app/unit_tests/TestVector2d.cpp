#include "pch.h"
#include "CppUnitTest.h"
#include "../../src/obj_tools.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace obj_tools;

namespace unittests
{
	TEST_CLASS(Vector2d)
	{
	public:

		TEST_METHOD(TestConstructors)
		{
			Vector2D v1;
			Assert::AreEqual(v1.getX(), 0.0f);
			Assert::AreEqual(v1.getY(), 0.0f);

			Vector2D v2 (2.0f, 3.0f);
			Assert::AreEqual(v2.getX(), 2.0f);
			Assert::AreEqual(v2.getY(), 3.0f);

			Vector2D v3(v2);
			Assert::AreEqual(v3.getX(), 2.0f);
			Assert::AreEqual(v3.getY(), 3.0f);
		}
		
		TEST_METHOD(TestAdditionOperators)
		{
			Vector2D rs(3, 5);

			Vector2D v1(2, 3);
			Vector2D v2(1, 2);
			Vector2D v3 = v1 + v2;
			Assert::IsTrue(v3 == rs);
		
			v2 += v1;
			Assert::IsTrue(v2 == rs);
		}

		TEST_METHOD(TestSubstractionOperators)
		{
			Vector2D rs(2, 3);
			Vector2D v1(3, 5);
			Vector2D v2(1, 2);
			Vector2D v3 = v1 - v2;
			Assert::IsTrue(v3 == rs);

			v1 -= v2;
			Assert::IsTrue(v1 == rs);
		}

		TEST_METHOD(TestMultiplyOperators)
		{
			Vector2D rs(4, 6);
			Vector2D v1(2, 3);
			Vector2D v2 = v1 * 2.0f;
			Assert::IsTrue(v2 == rs);

			Vector2D v3 = 2.0f * v1;
			Assert::IsTrue(v3 == rs);

			v1 *= 2.0;
			Assert::IsTrue(v1 == rs);
		}

		TEST_METHOD(TestDot)
		{
			Vector2D v1(2, 3);
			Vector2D v2(4, 5);
			
			Assert::AreEqual(v1.dot(v2), 2 * 4.0 + 3 * 5.0);
		}

		TEST_METHOD(TestNorm)
		{
			Vector2D v1(4, 5);

			Assert::AreEqual(v1.normSquared(), 4.0 * 4.0 + 5.0 * 5.0);
			Assert::AreEqual(v1.norm(), sqrt(v1.normSquared()));
		}

		TEST_METHOD(TestNormalize)
		{
			Vector2D v1(4, 5);
			Vector2D v2((float)(4/v1.norm()), (float)(5/ v1.norm()));

			Assert::IsTrue(fabs(v1.normalize(1e-6).getX() - v2.getX()) < 1e-6);
			Assert::IsTrue(fabs(v1.normalize(1e-6).getY() - v2.getY()) < 1e-6);
		}

		
	};
}
