#pragma once

#include "Calculator.h"

#include <QtTest>

class TestCalculator: public QObject
{
	Q_OBJECT

private slots:
	// -- setup/cleanup --
	void init();

	// -- tests data --
	void testDiff_data();

	// -- tests --
	void testConstructor();
	void testDiff();
	void testSum();

private:
	const int A0 = 0;
	const int B0 = 0;

private:
	Calculator mCalc;
};
