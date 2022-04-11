#include "pch.h"
#include "CppUnitTest.h"
#include "../PR3.2A/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UT32A
{
	TEST_CLASS(UT32A)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			double t;
			int N = 3;
			Student* s = new Student[N];

			s[0].inf = 5;
			s[1].inf = 5;
			s[2].inf = 5;
			s[0].kurs = 1;
			s[1].kurs = 1;
			s[2].kurs = 1;
			s[0].secondname = "1";
			s[0].secondname = "1";
			s[0].secondname = "1";

			t = BinSearch(s, N, 5, 1, "1");

			Assert::AreEqual(t, -1.);
		}
	};
}