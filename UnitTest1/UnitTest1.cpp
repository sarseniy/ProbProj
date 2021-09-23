#include "pch.h"
#include "CppUnitTest.h"
#include "../ProbProj/Prob.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(DiscrSta)
	{
	public:
		TEST_METHOD(DiscreteStateContains1)
		{
			DiscreteState t(1);
			Assert::AreEqual(t.contains(1), true);
			Assert::AreEqual(t.contains(5), false);
			Assert::AreEqual(t.contains(58), false);
		}
		TEST_METHOD(DiscreteStateContains2)
		{
			DiscreteState t(5);
			Assert::AreEqual(t.contains(1), false);
			Assert::AreEqual(t.contains(5), true);
			Assert::AreEqual(t.contains(17), false);
			Assert::AreEqual(t.contains(6), false);
		}
		TEST_METHOD(DiscreteStateContains3)
		{
			DiscreteState t(96);
			Assert::AreEqual(t.contains(92), false);
			Assert::AreEqual(t.contains(96), true);
			Assert::AreEqual(t.contains(97), false);
			Assert::AreEqual(t.contains(95), false);
		}
		TEST_METHOD(DiscreteStateContains4)
		{
			DiscreteState t(50);
			Assert::AreEqual(t.contains(50), true);
			Assert::AreEqual(t.contains(49), false);
			Assert::AreEqual(t.contains(51), false);
		}
	};
	TEST_CLASS(SegmSt)
	{
	public:
		TEST_METHOD(SegmentStateContains1)
		{
			SegmentState t(0, 10);
			Assert::AreEqual(t.contains(3), true);
			Assert::AreEqual(t.contains(10), true);
			Assert::AreEqual(t.contains(50), false);
		}
		TEST_METHOD(SegmentStateContains2)
		{
			SegmentState t(0, 10);
			Assert::AreEqual(t.contains(25), false);
			Assert::AreEqual(t.contains(10), true);
			Assert::AreEqual(t.contains(19), false);
		}
		TEST_METHOD(SegmentStateContains3)
		{
			SegmentState t(15, 17);
			Assert::AreEqual(t.contains(16), true);
			Assert::AreEqual(t.contains(14), false);
			Assert::AreEqual(t.contains(18), false);
		}
		TEST_METHOD(SegmentStateContains4)
		{
			SegmentState t(85, 96);
			Assert::AreEqual(t.contains(3), false);
			Assert::AreEqual(t.contains(85), true);
			Assert::AreEqual(t.contains(84), false);
		}
	};
	TEST_CLASS(SetSt)
	{
	public:
		TEST_METHOD(SetStateContains1)
		{
			SetState t({1});
			Assert::AreEqual(t.contains(0), false);
			Assert::AreEqual(t.contains(1), true);
			Assert::AreEqual(t.contains(2), false);
		}
		TEST_METHOD(SetStateContains2)
		{
			SetState t({ 1, 7 ,15 });
			Assert::AreEqual(t.contains(15), true);
			Assert::AreEqual(t.contains(1), true);
			Assert::AreEqual(t.contains(2), false);
		}
		TEST_METHOD(SetStateContains3)
		{
			SetState t({ 1, 55, 96, 35, 42 });
			Assert::AreEqual(t.contains(25), false);
			Assert::AreEqual(t.contains(1), true);
			Assert::AreEqual(t.contains(43), false);
		}
		TEST_METHOD(SetStateContains4)
		{
			SetState t({ 1, 55, 96, 35, 42 , 33, 27});
			Assert::AreEqual(t.contains(82), false);
			Assert::AreEqual(t.contains(1), true);
			Assert::AreEqual(t.contains(27), true);
			Assert::AreEqual(t.contains(28), false);
		}
	};
	TEST_CLASS(UnSt)
	{
	public:
		TEST_METHOD(SetAndDiscreteContains1)
		{
			SetState t1({ 1, 9 });
			DiscreteState t2(5);
			UnionState t(&t1, &t2);
			Assert::AreEqual(t.contains(1), true);
			Assert::AreEqual(t.contains(5), true);
			Assert::AreEqual(t.contains(9), true);
			Assert::AreEqual(t.contains(3), false);
		}
		TEST_METHOD(SetAndDiscreteContains2)
		{
			SetState t1({ 1, 9, 17 });
			DiscreteState t2(2);
			UnionState t(&t1, &t2);
			Assert::AreEqual(t.contains(85), false);
			Assert::AreEqual(t.contains(1), true);
			Assert::AreEqual(t.contains(17), true);
			Assert::AreEqual(t.contains(2), true);
		}
		TEST_METHOD(SetAndSegmentContains1)
		{
			SetState t1({ 1, 9 });
			SegmentState t2(5, 15);
			UnionState t(&t1, &t2);
			Assert::AreEqual(t.contains(14), true);
			Assert::AreEqual(t.contains(4), false);
			Assert::AreEqual(t.contains(16), false);
		}
		TEST_METHOD(SetAndSegmentContains2)
		{
			SetState t1({ 1, 9 });
			SegmentState t2(5, 15);
			UnionState t(&t1, &t2);
			Assert::AreEqual(t.contains(98), false);
			Assert::AreEqual(t.contains(1), true);
			Assert::AreEqual(t.contains(16), false);
		}
		TEST_METHOD(DiscreteAndSegmentContains1)
		{
			DiscreteState t1(10);
			SegmentState t2(5, 15);
			UnionState t(&t1, &t2);
			Assert::AreEqual(t.contains(10), true);
			Assert::AreEqual(t.contains(4), false);
			Assert::AreEqual(t.contains(16), false);
		}
		TEST_METHOD(DiscreteAndSegmentContains2)
		{
			DiscreteState t1(85);
			SegmentState t2(5, 15);
			UnionState t(&t1, &t2);
			Assert::AreEqual(t.contains(17), false);
			Assert::AreEqual(t.contains(85), true);
			Assert::AreEqual(t.contains(4), false);
		}
	};
	TEST_CLASS(SubstrSt)
	{
	public:
		TEST_METHOD(SetWODiscreteContains1)
		{
			SetState t1({ 1, 9 });
			DiscreteState t2(5);
			SubstractState t(&t1, &t2);
			Assert::AreEqual(t.contains(1), true);
			Assert::AreEqual(t.contains(9), true);
			Assert::AreEqual(t.contains(5), false);
			Assert::AreEqual(t.contains(0), false);
		}
		TEST_METHOD(SetWODiscreteContains2)
		{
			SetState t1({ 1, 9, 17 });
			DiscreteState t2(9);
			SubstractState t(&t1, &t2);
			Assert::AreEqual(t.contains(9), false);
			Assert::AreEqual(t.contains(1), true);
			Assert::AreEqual(t.contains(0), false);
		}
		TEST_METHOD(SetWOSegmentContains1)
		{
			SetState t1({ 1, 9 });
			SegmentState t2(5, 15);
			SubstractState t(&t1, &t2);
			Assert::AreEqual(t.contains(14), false);
			Assert::AreEqual(t.contains(15), false);
			Assert::AreEqual(t.contains(1), true);
			Assert::AreEqual(t.contains(0), false);
		}
		TEST_METHOD(SetWOSegmentContains2)
		{
			SetState t1({ 1, 9 });
			SegmentState t2(5, 15);
			SubstractState t(&t1, &t2);
			Assert::AreEqual(t.contains(1), true);
			Assert::AreEqual(t.contains(10), false);
			Assert::AreEqual(t.contains(16), false);
		}
		TEST_METHOD(DiscreteWOSegmentContains1)
		{
			DiscreteState t1(10);
			SegmentState t2(5, 15);
			SubstractState t(&t1, &t2);
			Assert::AreEqual(t.contains(10), false);
			Assert::AreEqual(t.contains(1), false);
			Assert::AreEqual(t.contains(99), false);
		}
		TEST_METHOD(DiscreteAndSegmentContains2)
		{
			DiscreteState t1(85);
			SegmentState t2(5, 15);
			SubstractState t(&t1, &t2);
			Assert::AreEqual(t.contains(85), true);
			Assert::AreEqual(t.contains(1), false);
			Assert::AreEqual(t.contains(96), false);
		}
	};
	TEST_CLASS(InterSt)
	{
	public:
		TEST_METHOD(SetIntDiscreteContains1)
		{
			SetState t1({ 1, 9 });
			DiscreteState t2(9);
			IntersectState t(&t1, &t2);
			Assert::AreEqual(t.contains(9), true);
			Assert::AreEqual(t.contains(1), false);
			Assert::AreEqual(t.contains(10), false);
			Assert::AreEqual(t.contains(8), false);
		}
		TEST_METHOD(SetIntDiscreteContains2)
		{
			SetState t1({ 1, 9, 17 });
			DiscreteState t2(9);
			IntersectState t(&t1, &t2);
			Assert::AreEqual(t.contains(17), false);
			Assert::AreEqual(t.contains(1), false);
			Assert::AreEqual(t.contains(9), true);
			Assert::AreEqual(t.contains(10), false);
		}
		TEST_METHOD(SetIntSegmentContains1)
		{
			SetState t1({ 1, 9 });
			SegmentState t2(5, 15);
			IntersectState t(&t1, &t2);
			Assert::AreEqual(t.contains(9), true);
			Assert::AreEqual(t.contains(1), false);
			Assert::AreEqual(t.contains(10), false);
		}
		TEST_METHOD(SetIntSegmentContains2)
		{
			SetState t1({ 1, 9 });
			SegmentState t2(5, 15);
			IntersectState t(&t1, &t2);
			Assert::AreEqual(t.contains(1), false);
			Assert::AreEqual(t.contains(9), true);
			Assert::AreEqual(t.contains(10), false);
			Assert::AreEqual(t.contains(81), false);
		}
		TEST_METHOD(DiscreteIntSegmentContains1)
		{
			DiscreteState t1(10);
			SegmentState t2(5, 15);
			IntersectState t(&t1, &t2);
			Assert::AreEqual(t.contains(10), true);
			Assert::AreEqual(t.contains(1), false);
			Assert::AreEqual(t.contains(5), false);
			Assert::AreEqual(t.contains(11), false);
		}
		TEST_METHOD(DiscreteIntSegmentContains2)
		{
			DiscreteState t1(85);
			SegmentState t2(5, 15);
			IntersectState t(&t1, &t2);
			Assert::AreEqual(t.contains(2), false);
			Assert::AreEqual(t.contains(16), false);
			Assert::AreEqual(t.contains(14), false);
			Assert::AreEqual(t.contains(4), false);
		}
	};
}
