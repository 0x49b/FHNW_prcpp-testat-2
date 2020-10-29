#include "stdafx.h"
#include "CppUnitTest.h"

#include "../MySet/MySet.h"
#include "../MySet/OrderedSet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(TestMySet)
	{
	public:

		TEST_METHOD(Creation)
		{
			Set s1;
			Set s11(s1);
			Set s4({ 5,4,3,2,1 });
			Set s41(s4);
			Set s42 = s4;
		}

		TEST_METHOD(Containing)
		{
			Assert::IsFalse(Set().contains(1));

			Set s1({ 1,2,3 });
			Assert::IsTrue(s1.contains(1));
			Assert::IsTrue(s1.contains(2));
			Assert::IsTrue(s1.contains(3));
			Assert::IsFalse(s1.contains(0));

			Set s2({ 2,1 });
			Assert::IsTrue(s1.containsAll(s2));
			Assert::IsFalse(s2.containsAll(s1));
			Assert::IsFalse(Set().containsAll(s1));
			Assert::IsTrue(s1.containsAll(Set()));
		}

		TEST_METHOD(Empty)
		{
			Assert::IsTrue(Set().isEmpty());
			Assert::IsFalse(Set({ 1,2,3 }).isEmpty());
		}

		TEST_METHOD(Size)
		{
			Assert::AreEqual(Set().size(), (size_t)0);
			Assert::AreEqual(Set({ 1,2,3 }).size(), (size_t)3);
			Assert::AreEqual(Set({ 1,1,2,2,3,3,1,2,3 }).size(), (size_t)3);
		}

		TEST_METHOD(Union)
		{
			Set s1({ 1,2,3 });
			Set s2({ 3,2,4 });
			Set s3({ 1,2,3,4 });

			Assert::IsTrue(Set::merge(s1, s2) == s3);
			Assert::IsTrue(Set::merge(s1, Set()) == s1);
			Assert::IsTrue(Set::merge(Set(), s1) == s1);
		}

		TEST_METHOD(Difference)
		{
			Set s1({ 1,2,3 });
			Set s2({ 3,2,4 });

			Assert::IsTrue(Set::difference(s1, s2) == Set({ 1 }));
			Assert::IsTrue(Set::difference(s2, s1) == Set({ 4 }));
			Assert::IsTrue(Set::difference(s1, s1) == Set());
			Assert::IsTrue(Set::difference(Set(), s1) == Set());
			Assert::IsTrue(Set::difference(s1, Set()) == s1);
		}

		TEST_METHOD(Intersection)
		{
			Set s1({ 1,2,3 });
			Set s2({ 3,2,4 });

			Assert::IsTrue(Set::intersection(s1, s2) == Set({ 3,2 }));
			Assert::IsTrue(Set::intersection(s1, Set({ 4,5 })) == Set());
			Assert::IsTrue(Set::intersection(s1, s2) == Set::intersection(s2, s1));
			Assert::IsTrue(Set::intersection(Set(), s1) == Set());
			Assert::IsTrue(Set::intersection(s1, Set()) == Set());
		}

		TEST_METHOD(MoveSemantics) {
			Set s1({ 1,2,3 });
			Set s2({ 3,2,4 });
			Set s3({ 2,3 });
			Set s4({ 1 });

			// test move intersection
			Assert::IsTrue(Set::intersection(s1, Set(s2)) == s3);
			Assert::IsTrue(Set::intersection(Set(s1), s2) == s3);
			Assert::IsTrue(Set::intersection(Set(s1), Set(s2)) == s3);
			Assert::IsTrue(Set::intersection(s1, Set({ 3,2,4 })) == s3);
			Assert::IsTrue(Set::intersection(Set({ 1,2,3 }), s2) == s3);
			Assert::IsTrue(Set::intersection(Set({ 1,2,3 }), Set({ 3,2,4 })) == s3);
			Assert::IsTrue(Set::intersection(s1, std::move(s2)) == s3);
			Assert::IsTrue(s2 == s3);
			Assert::AreEqual(s2.size(), s3.size());

			// test move difference
			Assert::IsTrue(Set::difference(s1, Set(s3)) == s4);
			Assert::IsTrue(Set::difference(Set(s1), s3) == s4);
			Assert::IsTrue(Set::difference(Set(s1), Set(s3)) == s4);
			Assert::IsTrue(Set::difference(s1, Set({ 2,3 })) == s4);
			Assert::IsTrue(Set::difference(Set({ 1,2,3 }), s3) == s4);
			Assert::IsTrue(Set::difference(Set({ 1,2,3 }), Set({ 2,3 })) == s4);
			Assert::IsTrue(Set::difference(std::move(s1), s3) == s4);
			Assert::IsTrue(s1 == s4);
			Assert::AreEqual(s1.size(), s4.size());
		}

		TEST_METHOD(Union_Ordered) {
			OrderedSet s1({ 3,2,1,1,2 });
			OrderedSet s2({ 3,2,4 });
			OrderedSet s3({ 1,2,3,4 });

			Assert::IsTrue(Set::merge(OrderedSet({ 1,2 }), OrderedSet({ 3,4 })) == s3);
			Assert::IsTrue(Set::merge(s1, s2) == s3);
			Assert::IsTrue(Set::merge(s1, OrderedSet()) == s1);
			Assert::IsTrue(Set::merge(OrderedSet(), s1) == s1);
		}

		TEST_METHOD(Combined) {
			OrderedSet s1({ 5,4,3,2,1 });
			OrderedSet s2 = s1.getLarger(2); // {3,4,5}
			OrderedSet s3 = s1.getSmaller(4); // {1,2,3}

			Assert::IsTrue(s2 == OrderedSet({ 3,4,5 }));
			Assert::IsTrue(s2.getSmaller(2) == OrderedSet());
			Assert::IsTrue(s2.getSmaller(3) == OrderedSet());
			Assert::IsTrue(s2.getSmaller(4) == OrderedSet({ 3 }));
			Assert::IsTrue(s2.getSmaller(5) == OrderedSet({ 3,4 }));
			Assert::IsTrue(s2.getSmaller(10) == OrderedSet({ 3,4,5 }));

			Assert::IsTrue(s3 == OrderedSet({ 1,2,3 }));
			Assert::IsTrue(s3.getLarger(0) == OrderedSet({ 1,2,3 }));
			Assert::IsTrue(s3.getLarger(1) == OrderedSet({ 2,3 }));
			Assert::IsTrue(s3.getLarger(2) == OrderedSet({ 3 }));
			Assert::IsTrue(s3.getLarger(3) == OrderedSet());

			Assert::IsTrue(Set::merge(s2, OrderedSet({ 2,1 })) == s1);
			Assert::IsTrue(Set::merge(OrderedSet({ 2,1 }), s2) == s1);
			Assert::IsTrue(Set::merge(s3, OrderedSet({ 5,4 })) == s1);
			Assert::IsTrue(Set::merge(OrderedSet({ 5,4 }), s3) == s1);
			Assert::IsTrue(Set::merge(s2, s3) == s1);
			Assert::IsTrue(Set::merge(s3, s2) == s1);

		}

		TEST_METHOD(Smaller) {
			OrderedSet s1({ 1,2,3,20,13,9 });
			OrderedSet s2 = s1.getSmaller(13);

			Assert::IsTrue(s1.getSmaller(10) == OrderedSet({ 1,2,3,9 }));
			Assert::IsTrue(s1.getSmaller(9) == OrderedSet({ 1,2,3 }));
			Assert::IsTrue(s1.getSmaller(100) == s1);
			Assert::IsTrue(s1.getSmaller(20) == OrderedSet({ 1,2,3,9,13 }));
			Assert::IsTrue(s1.getSmaller(2) == OrderedSet({ 1 }));
			Assert::IsTrue(s1.getSmaller(1) == OrderedSet());
			Assert::IsTrue(s1.getSmaller(0) == OrderedSet());
			Assert::IsTrue(s1.getSmaller(-10) == OrderedSet());

			Assert::IsTrue(s2 == OrderedSet({ 1,2,3,9 }));
			Assert::IsTrue(s2.getSmaller(20) == OrderedSet({ 1,2,3,9 }));
			Assert::IsTrue(s2.getSmaller(13) == OrderedSet({ 1,2,3,9 }));
			Assert::IsTrue(s2.getSmaller(9) == OrderedSet({ 1,2,3 }));
			Assert::IsTrue(s2.getSmaller(2) == OrderedSet({ 1 }));
			Assert::IsTrue(s2.getSmaller(1) == OrderedSet());
			Assert::IsTrue(s2.getSmaller(-10) == OrderedSet());
		}

		TEST_METHOD(Larger) {
			OrderedSet s1({ 1,2,3,20,13,9 });
			OrderedSet s2 = s1.getLarger(3);

			Assert::IsTrue(s1.getLarger(2) == OrderedSet({ 3,9,13,20 }));
			Assert::IsTrue(s1.getLarger(3) == OrderedSet({ 9,13,20 }));
			Assert::IsTrue(s1.getLarger(100) == OrderedSet());
			Assert::IsTrue(s1.getLarger(20) == OrderedSet());
			Assert::IsTrue(s1.getLarger(13) == OrderedSet({ 20 }));
			Assert::IsTrue(s1.getLarger(1) == OrderedSet({ 2,3,20,13,9 }));
			Assert::IsTrue(s1.getLarger(0) == s1);

			Assert::IsTrue(s2 == OrderedSet({ 9,13,20 }));
			Assert::IsTrue(s2.getLarger(3) == OrderedSet({ 9,13,20 }));
			Assert::IsTrue(s2.getLarger(10) == OrderedSet({ 13,20 }));
			Assert::IsTrue(s2.getLarger(13) == OrderedSet({ 20 }));
			Assert::IsTrue(s2.getLarger(20) == OrderedSet());
			Assert::IsTrue(s2.getLarger(21) == OrderedSet());
		}
	};
}
