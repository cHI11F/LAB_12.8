#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB_12.8/LAB_12.8.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			// Arrange
			Node* testList = nullptr;

			// Act
			appendToList(testList, "1");
			appendToList(testList, "2");
			appendToList(testList, "3");

			// Assert
			Assert::IsTrue(contains(testList, 1));
			Assert::IsTrue(contains(testList, 2));
			Assert::IsTrue(contains(testList, 3));
			Assert::IsFalse(contains(testList, 4));

			// Clean up
			freeList(testList);
		}
	};
}
