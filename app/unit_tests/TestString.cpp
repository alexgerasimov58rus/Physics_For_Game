#include "pch.h"
#include "CppUnitTest.h"
#include "../../src/obj_tools.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace obj_tools;
using namespace std;

namespace unittests
{
	TEST_CLASS(TestString)
	{
	public:

		TEST_METHOD(TestSplit)
		{
			string s = "123 456 789";
			vector<string> vec = String::split(s, ' ');

			Assert::AreEqual((int)vec.size(), 3);
			Assert::AreEqual(string("123"), vec[0]);
			Assert::AreEqual(string("456"), vec[1]);
			Assert::AreEqual(string("789"), vec[2]);

			s = "1//2";
			vec = String::split(s, '/');

			Assert::AreEqual((int)vec.size(), 3);
			Assert::AreEqual(string("1"), vec[0]);
			Assert::IsTrue(vec[1].empty());
			Assert::AreEqual(string("2"), vec[2]);
		}
	};
};