#pragma once

#include "IntBitset.h"

#include <QtTest>

class TestIntBitset: public QObject
{
	Q_OBJECT

private slots:
	// -- setup/cleanup --
	void cleanupTestCase();
	void initTestCase();
	void init();

	// -- tests --
	void testOperators();
	void testSetAllOff();
	void testSetAllOn();
	void testSetOff();
	void testSetOn();

private:
	IntBitset mBS;
};
