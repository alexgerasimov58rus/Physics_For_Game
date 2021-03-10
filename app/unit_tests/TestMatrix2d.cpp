#include "pch.h"
#include "CppUnitTest.h"
#include "../../src/obj_tools.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace obj_tools;

namespace unittests
{
	TEST_CLASS(Matrix2d)
	{
	public:

		TEST_METHOD(TestConstructors)
		{
			Matrix2x2 m;
			
			Assert::AreEqual(m.getElement(0, 0), 1.0f);
			Assert::AreEqual(m.getElement(1, 1), 1.0f);
			Assert::AreEqual(m.getElement(0, 1), 0.0f);
			Assert::AreEqual(m.getElement(1, 0), 0.0f);

			m.setElement(-1, -1, 2.0f);
			m.setElement( 2,  2, 3.0f);

			Assert::AreEqual(m.getElement(0, 0), 2.0f);
			Assert::AreEqual(m.getElement(1, 1), 3.0f);
		}

		TEST_METHOD(TestAdditionOperators)
		{
			Matrix2x2 rs;

			rs.setElement(0, 0, 2.0f);
			rs.setElement(0, 1, 2.0f);
			rs.setElement(1, 0, 3.0f);
			rs.setElement(1, 1, 5.0f);

			Matrix2x2 m1;
			Matrix2x2 m2;
			
			m2.setElement(0, 0, 1.0f);
			m2.setElement(0, 1, 2.0f);
			m2.setElement(1, 0, 3.0f);
			m2.setElement(1, 1, 4.0f);

			Assert::IsTrue((m1 + m2) == rs);
			m1 += m2;
			Assert::IsTrue(m1 == rs);
		}

		TEST_METHOD(TestSubstractionOperators)
		{
			Matrix2x2 rs;

			rs.setElement(0, 0, 0.0f);
			rs.setElement(0, 1, 2.0f);
			rs.setElement(1, 0, 3.0f);
			rs.setElement(1, 1, 3.0f);

			Matrix2x2 m1;
			Matrix2x2 m2;

			m1.setElement(0, 0, 1.0f);
			m1.setElement(0, 1, 2.0f);
			m1.setElement(1, 0, 3.0f);
			m1.setElement(1, 1, 4.0f);

			Assert::IsTrue((m1 - m2) == rs);
			m1 -= m2;
			Assert::IsTrue(m1 == rs);
		}

		TEST_METHOD(TestMultiplyScalar)
		{
			Matrix2x2 rs;

			rs.setElement(0, 0, 2.0f);
			rs.setElement(0, 1, 4.0f);
			rs.setElement(1, 0, 6.0f);
			rs.setElement(1, 1, 8.0f);

			Matrix2x2 m1;

			m1.setElement(0, 0, 1.0f);
			m1.setElement(0, 1, 2.0f);
			m1.setElement(1, 0, 3.0f);
			m1.setElement(1, 1, 4.0f);

			Assert::IsTrue((m1 * 2.0f) == rs);
			Assert::IsTrue((2.0f * m1) == rs);

			m1 *= 2.0f;
			Assert::IsTrue(m1 == rs);
		}

		TEST_METHOD(TestMultiplyMatrix)
		{
			Matrix2x2 rs;
			rs.setElement(0, 0, 2.0f);
			rs.setElement(0, 1, 0.0f);
			rs.setElement(1, 0, 0.0f);
			rs.setElement(1, 1, 2.0f);

			Matrix2x2 m1;
			m1.setElement(0, 0, 1.0f);
			m1.setElement(0, 1, 2.0f);
			m1.setElement(1, 0, 3.0f);
			m1.setElement(1, 1, 4.0f);

			Matrix2x2 m2;
			m2.setElement(0, 0, -4.0f);
			m2.setElement(0, 1, 2.0f);
			m2.setElement(1, 0, 3.0f);
			m2.setElement(1, 1, -1.0f);

			Assert::IsTrue(m1 * m2 == rs);
		}

		TEST_METHOD(TestTransposition)
		{
			Matrix2x2 rs;
			rs.setElement(0, 0, 1.0f);
			rs.setElement(0, 1, 3.0f);
			rs.setElement(1, 0, 2.0f);
			rs.setElement(1, 1, 4.0f);

			Matrix2x2 m1;
			m1.setElement(0, 0, 1.0f);
			m1.setElement(0, 1, 2.0f);
			m1.setElement(1, 0, 3.0f);
			m1.setElement(1, 1, 4.0f);
		
			Assert::IsTrue(m1.transposition() == rs);
		}

		TEST_METHOD(TestDeterminant)
		{
			Matrix2x2 m1;
			m1.setElement(0, 0, 1.0f);
			m1.setElement(0, 1, 2.0f);
			m1.setElement(1, 0, 3.0f);
			m1.setElement(1, 1, 4.0f);

			Assert::AreEqual(m1.determinant(), 1.0f * 4.0f - 2.0f * 3.0f);
		}

		TEST_METHOD(TestInverse)
		{
			Matrix2x2 m1;
			m1.setElement(0, 0, 1.0f);
			m1.setElement(0, 1, 2.0f);
			m1.setElement(1, 0, 3.0f);
			m1.setElement(1, 1, 4.0f);

			Matrix2x2 m2 = m1.inverse();

			Matrix2x2 rs;
			rs.setElement(0, 0, -2.0f);
			rs.setElement(0, 1, 1.0f);
			rs.setElement(1, 0, 1.5f);
			rs.setElement(1, 1, -0.5f);


			Assert::IsTrue(m2 == rs);
		}
	};
};