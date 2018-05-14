#include "TestIntBitset.h"

const unsigned int BITS_IN_BYTE	= 8;
const unsigned int BITS_IN_INT	= BITS_IN_BYTE * sizeof(int);

// -- setup/cleanup --
void TestIntBitset::cleanupTestCase()
{
	if(sizeof(int) != 4)
		QFAIL("Int size is not 4 on this platform.");
}

void TestIntBitset::initTestCase()
{
    if(sizeof(int) != 4)
		QFAIL("Int size is not 4 on this platform.");
}

void TestIntBitset::init()
{
	// clear the bitset before every test
	mBS.setAllOff();
}

// -- tests --
void TestIntBitset::testOperators()
{
	QSKIP("Operators have not been implemented yet...");
}

void TestIntBitset::testSetAllOff()
{
	mBS.setAllOff();

	QCOMPARE(mBS.getNumBitsOn(), 0u);
	QCOMPARE(mBS.getNumBitsOff(), BITS_IN_INT);

	QVERIFY2(!mBS.isAllOn(), "setAllOff() failed.");
	QVERIFY2(mBS.isAllOff(), "setAllOff() failed.");

}

void TestIntBitset::testSetAllOn()
{
	mBS.setAllOn();

	QCOMPARE(mBS.getNumBitsOn(), BITS_IN_INT);
	QCOMPARE(mBS.getNumBitsOff(), 0u);

	QVERIFY2(mBS.isAllOn(), "setAllOn() failed.");
	QVERIFY2(!mBS.isAllOff(), "setAllOn() failed.");
}

void TestIntBitset::testSetOff()
{
	mBS.setAllOn();

	unsigned int bitsOff = 0;
	mBS.setBitOff(BITS_IN_BYTE * bitsOff++);
	mBS.setBitOff(BITS_IN_BYTE * bitsOff++);
	mBS.setBitOff(BITS_IN_BYTE * bitsOff++);
	mBS.setBitOff(BITS_IN_BYTE * bitsOff++);

	QEXPECT_FAIL("", "isAnyOff not implemented yet", Continue);
	QVERIFY(mBS.isAnyOff());

	QCOMPARE(mBS.getNumBitsOff(), bitsOff);

	// this test will trigger a warning
	if((BITS_IN_BYTE * bitsOff) < BITS_IN_INT)
		QVERIFY(!mBS.isBitOff(BITS_IN_BYTE * bitsOff));
	else
		QWARN("trying to verify bit out of set bounds");

	QVERIFY(mBS.isBitOff(BITS_IN_BYTE * --bitsOff));
	QVERIFY(mBS.isBitOff(BITS_IN_BYTE * --bitsOff));
	QVERIFY(mBS.isBitOff(BITS_IN_BYTE * --bitsOff));
	QVERIFY(mBS.isBitOff(BITS_IN_BYTE * --bitsOff));
}

void TestIntBitset::testSetOn()
{
	unsigned int bitsOn = 0;
	mBS.setBitOn(BITS_IN_BYTE * bitsOn++);
	mBS.setBitOn(BITS_IN_BYTE * bitsOn++);

	if(BITS_IN_BYTE * bitsOn)

	QVERIFY(mBS.isAnyOn());

	QCOMPARE(mBS.getNumBitsOn(), bitsOn);

	if((BITS_IN_BYTE * bitsOn) < BITS_IN_INT)
		QVERIFY(!mBS.isBitOn(BITS_IN_BYTE * bitsOn));
	else
		QWARN("trying to verify value out of set bounds");

	QVERIFY(mBS.isBitOn(BITS_IN_BYTE * --bitsOn));
	QVERIFY(mBS.isBitOn(BITS_IN_BYTE * --bitsOn));
}

// generate basic main: no GUI, no events
QTEST_APPLESS_MAIN(TestIntBitset)
