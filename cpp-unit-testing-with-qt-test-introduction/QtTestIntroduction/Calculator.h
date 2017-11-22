#pragma once

// example class to test
class Calculator
{
public:
    Calculator(int a = 0, int b = 0) : mA(a), mB(b) { }

    int GetA() const { return mA; }
    void SetA(int a) { mA = a; }
    int GetB() const { return mB; }
    void SetB(int b) { mB = b; }

    int Sum() const { return mA + mB; }
    int Diff() const { return mA - mB; }
    int Mult() const { return mA * mB; }
    int Div() const { return mA / mB; }

private:
    int mA;
    int mB;
};

