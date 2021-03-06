#include "pch.h"
#include "CppUnitTest.h"
#include "../../src/obj_tools.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace obj_tools;
using namespace std;

namespace unittests
{
	TEST_CLASS(TestMesh)
	{
	public:

		TEST_METHOD(TestLoadFromObjFile)
		{
			Mesh m("Cube");
			Assert::IsTrue(m.loadFromObjFile("../../../../data/.obj/test.obj"));
			Assert::IsFalse(m.loadFromObjFile("../../../../data/.obj/test_1.obj"));
			Assert::IsFalse(m.loadFromObjFile("../../../../data/.obj/test_2.obj"));
		}

		TEST_METHOD(TestCalcBoundingSphereRadius)
		{
			Mesh m("Sphere");
			Assert::IsTrue(m.loadFromObjFile("../../../../data/.obj/sphere.obj"));
			m.compile();
			Assert::IsTrue(fabs(m.getBoundingSphereRadius() - 1.0) < 1e-6);
		}
	};
};