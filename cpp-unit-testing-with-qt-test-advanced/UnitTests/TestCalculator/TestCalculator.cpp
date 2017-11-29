#include "TestCalculator.h"

// -- setup/cleanup --
void TestCalculator::init()
{
	mCalc.SetA(A0);
	mCalc.SetB(B0);
}

// -- tests data --
void TestCalculator::testDiff_data()
{
	QTest::addColumn<int>("a");
	QTest::addColumn<int>("b");
	QTest::addColumn<int>("result");

	QTest::newRow("all 0") << 0 << 0 << 0;
	QTest::newRow("same number") << 10 << 10 << 0;
	QTest::newRow("opposite number") << 10 << -10 << 20;
	QTest::newRow("positive res") << 10 << 5 << 5;
	QTest::newRow("negative res") << 5 << 10 << -5;
}

// -- tests --
void TestCalculator::testConstructor()
{
	// default values
	Calculator c1;

	QVERIFY(c1.GetA() == 0);
	QVERIFY(c1.GetB() == 0);

	// full constructor
	const int A = 10;
	const int B = 2;
	Calculator c2(A, B);

	QVERIFY2(c2.GetA() == A, "first operand doesn't match");
	QVERIFY2(c2.GetB() == B, "second operand doesn't match");
}

void TestCalculator::testDiff()
{
	// retrieve data
	QFETCH(int, a);
	QFETCH(int, b);
	QFETCH(int, result);

	// set values
	mCalc.SetA(a);
	mCalc.SetB(b);

	// test
	QCOMPARE(mCalc.Diff(), result);
}


void TestCalculator::testSum()
{
	// sum default
	QCOMPARE(mCalc.Sum(), A0 + B0);

	// sum after setting a and b
	const int A = 10;
	const int B = 2;
	mCalc.SetA(A);
	mCalc.SetB(B);

	QCOMPARE(mCalc.Sum(), A + B);
}

// generate basic main: no GUI, no events
QTEST_APPLESS_MAIN(TestCalculator)

// uncomment next line if class declaration is in .cpp (no .h)
//#include "TestCalculator.moc"
