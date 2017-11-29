#pragma once

class IntBitset
{
public:
	IntBitset() : mData(0) { }

	void setAllOff() { mData = 0; }
	void setAllOn() { mData = 0xFFFFFFFF; }
	void setBitOff(unsigned int index) { mData &= ~(1 << index); }
	void setBitOn(unsigned int index) { mData |= 1 << index; }

	bool isAllOff() { return 0 == mData ; }
	bool isAnyOff() { return false; } // TODO for example
	bool isAllOn() { return 0xFFFFFFFF == mData; }
	bool isAnyOn() { return mData != 0; }
	bool isBitOn(unsigned int index) { return mData & (1 << index); }
	bool isBitOff(unsigned int index) { return !(mData & (1 << index)); }

	unsigned int getNumBitsOn();
	unsigned int getNumBitsOff();

private:
	unsigned int mData;
};
