#include "IntBitset.h"

const unsigned int NUM_BITS = sizeof(int) * 8;

unsigned int IntBitset::getNumBitsOn()
{
	unsigned int numOn = 0;

	for(unsigned int ind = 0; ind < NUM_BITS; ++ind)
	{
		if(mData & (1 << ind))
			++numOn;
	}

	return numOn;
}

unsigned int IntBitset::getNumBitsOff()
{
	unsigned int numOn = 0;

	for(unsigned int ind = 0; ind < NUM_BITS; ++ind)
	{
		if(!(mData & (1 << ind)))
			++numOn;
	}

	return numOn;
}
