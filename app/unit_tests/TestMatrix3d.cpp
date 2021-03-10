#include "pch.h"
#include "CppUnitTest.h"
#include "../../src/obj_tools.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace obj_tools;

namespace unittests
{
	TEST_CLASS(Matrix3d)
	{
	public:

		TEST_METHOD(TestConstructors)
		{
			Matrix3x3 m;

			Assert::AreEqual(m.getElement(0, 0), 1.0f);
			Assert::AreEqual(m.getElement(1, 1), 1.0f);
			Assert::AreEqual(m.getElement(0, 1), 0.0f);
			Assert::AreEqual(m.getElement(1, 0), 0.0f);
			Assert::AreEqual(m.getElement(2, 2), 1.0f);

			m.setElement(-1, -1, 2.0f);
			m.setElement( 3,  3, 3.0f);

			Assert::AreEqual(m.getElement(0, 0), 2.0f);
			Assert::AreEqual(m.getElement(2, 2), 3.0f);
		}

		TEST_METHOD(TestAdditionOperators)
		{
			Matrix3x3 rs;

			rs.setElement(0, 0, 2.0f);
			rs.setElement(0, 1, 2.0f);
			rs.setElement(0, 2, 3.0f);
			rs.setElement(1, 0, 4.0f);
			rs.setElement(1, 1, 6.0f);
			rs.setElement(1, 2, 6.0f);
			rs.setElement(2, 0, 7.0f);
			rs.setElement(2, 1, 8.0f);
			rs.setElement(2, 2, 10.0f);

			Matrix3x3 m1;
			Matrix3x3 m2;

			m2.setElement(0, 0, 1.0f);
			m2.setElement(0, 1, 2.0f);
			m2.setElement(0, 2, 3.0f);
			m2.setElement(1, 0, 4.0f);
			m2.setElement(1, 1, 5.0f);
			m2.setElement(1, 2, 6.0f);
			m2.setElement(2, 0, 7.0f);
			m2.setElement(2, 1, 8.0f);
			m2.setElement(2, 2, 9.0f);


			Assert::IsTrue((m1 + m2) == rs);
			m1 += m2;
			Assert::IsTrue(m1 == rs);
		}

		TEST_METHOD(TestSubstractionOperators)
		{
			Matrix3x3 rs;

			rs.setElement(0, 0, 0.0f);
			rs.setElement(0, 1, 2.0f);
			rs.setElement(0, 2, 3.0f);
			rs.setElement(1, 0, 4.0f);
			rs.setElement(1, 1, 4.0f);
			rs.setElement(1, 2, 6.0f);
			rs.setElement(2, 0, 7.0f);
			rs.setElement(2, 1, 8.0f);
			rs.setElement(2, 2, 8.0f);

			Matrix3x3 m1;
			Matrix3x3 m2;

			m1.setElement(0, 0, 1.0f);
			m1.setElement(0, 1, 2.0f);
			m1.setElement(0, 2, 3.0f);
			m1.setElement(1, 0, 4.0f);
			m1.setElement(1, 1, 5.0f);
			m1.setElement(1, 2, 6.0f);
			m1.setElement(2, 0, 7.0f);
			m1.setElement(2, 1, 8.0f);
			m1.setElement(2, 2, 9.0f);


			Assert::IsTrue((m1 - m2) == rs);
			m1 -= m2;
			Assert::IsTrue(m1 == rs);
		}

		TEST_METHOD(TestMultiplyScalar)
		{
			Matrix3x3 rs;

			rs.setElement(0, 0, 2.0f);
			rs.setElement(0, 1, 4.0f);
			rs.setElement(0, 2, 6.0f);
			rs.setElement(1, 0, 8.0f);
			rs.setElement(1, 1, 10.0f);
			rs.setElement(1, 2, 12.0f);
			rs.setElement(2, 0, 14.0f);
			rs.setElement(2, 1, 16.0f);
			rs.setElement(2, 2, 18.0f);

			Matrix3x3 m1;

			m1.setElement(0, 0, 1.0f);
			m1.setElement(0, 1, 2.0f);
			m1.setElement(0, 2, 3.0f);
			m1.setElement(1, 0, 4.0f);
			m1.setElement(1, 1, 5.0f);
			m1.setElement(1, 2, 6.0f);
			m1.setElement(2, 0, 7.0f);
			m1.setElement(2, 1, 8.0f);
			m1.setElement(2, 2, 9.0f);

			Assert::IsTrue((m1 * 2.0f) == rs);
			Assert::IsTrue((2.0f * m1) == rs);

			m1 *= 2.0f;
			Assert::IsTrue(m1 == rs);
		}

		TEST_METHOD(TestMultiplyMatrix)
		{
			Matrix3x3 rs;
			rs.setElement(0, 0, -30.0f);
			rs.setElement(0, 1,  36.0f);
			rs.setElement(0, 2,  42.0f);
			rs.setElement(1, 0, -66.0f);
			rs.setElement(1, 1,  81.0f);
			rs.setElement(1, 2,  96.0f);
			rs.setElement(2, 0, -102.0f);
			rs.setElement(2, 1,  126.0f);
			rs.setElement(2, 2,  150.0f);

			Matrix3x3 m1;
			m1.setElement(0, 0, 1.0f);
			m1.setElement(0, 1, 2.0f);
			m1.setElement(0, 2, 3.0f);
			m1.setElement(1, 0, 4.0f);
			m1.setElement(1, 1, 5.0f);
			m1.setElement(1, 2, 6.0f);
			m1.setElement(2, 0, 7.0f);
			m1.setElement(2, 1, 8.0f);
			m1.setElement(2, 2, 9.0f);

			Matrix3x3 m2;
			m1.setElement(0, 0, -1.0f);
			m1.setElement(0, 1, 2.0f);
			m1.setElement(0, 2, 3.0f);
			m1.setElement(1, 0, -4.0f);
			m1.setElement(1, 1, 5.0f);
			m1.setElement(1, 2, 6.0f);
			m1.setElement(2, 0, -7.0f);
			m1.setElement(2, 1, 8.0f);
			m1.setElement(2, 2, 9.0f);

			rs = m1 * m2;

			Assert::IsTrue(m1 * m2 == rs);
		}

		TEST_METHOD(TestTransposition)
		{
			Matrix3x3 rs;
			rs.setElement(0, 0, 1.0f);
			rs.setElement(1, 0, 2.0f);
			rs.setElement(2, 0, 3.0f);
			rs.setElement(0, 1, 4.0f);
			rs.setElement(1, 1, 5.0f);
			rs.setElement(2, 1, 6.0f);
			rs.setElement(0, 2, 7.0f);
			rs.setElement(1, 2, 8.0f);
			rs.setElement(2, 2, 9.0f);

			Matrix3x3 m1;
			m1.setElement(0, 0, 1.0f);
			m1.setElement(0, 1, 2.0f);
			m1.setElement(0, 2, 3.0f);
			m1.setElement(1, 0, 4.0f);
			m1.setElement(1, 1, 5.0f);
			m1.setElement(1, 2, 6.0f);
			m1.setElement(2, 0, 7.0f);
			m1.setElement(2, 1, 8.0f);
			m1.setElement(2, 2, 9.0f);

			Assert::IsTrue(m1.transposition() == rs);
		}

		TEST_METHOD(TestDeterminant)
		{
			Matrix3x3 m1;
			m1.setElement(0, 0, 3.0f);
			m1.setElement(0, 1, 2.0f);
			m1.setElement(0, 2, 3.0f);
			m1.setElement(1, 0, 4.0f);
			m1.setElement(1, 1, 5.0f);
			m1.setElement(1, 2, 6.0f);
			m1.setElement(2, 0, 7.0f);
			m1.setElement(2, 1, 8.0f);
			m1.setElement(2, 2, 9.0f);

			Assert::AreEqual(m1.determinant(), -6.0f);
		}

		TEST_METHOD(TestInverse)
		{
			Matrix3x3 m1;
			m1.setElement(0, 0, 3.0f);
			m1.setElement(0, 1, 2.0f);
			m1.setElement(0, 2, 3.0f);
			m1.setElement(1, 0, 4.0f);
			m1.setElement(1, 1, 5.0f);
			m1.setElement(1, 2, 6.0f);
			m1.setElement(2, 0, 7.0f);
			m1.setElement(2, 1, 8.0f);
			m1.setElement(2, 2, 9.0f);

			Matrix3x3 m2 = m1.inverse();

			Matrix3x3 rs;
			rs.setElement(0, 0, 0.5f);
			rs.setElement(0, 1,-1.0f);
			rs.setElement(0, 2, 0.5f);
			rs.setElement(1, 0,-1.0f);
			rs.setElement(1, 1,-1.0f);
			rs.setElement(1, 2, 1.0f);
			rs.setElement(2, 0, 0.5f);
			rs.setElement(2, 1, 5 / 3.0f);
			rs.setElement(2, 2,-7 / 6.0f);

			Assert::IsTrue(m2 == rs);
		}
	};
};