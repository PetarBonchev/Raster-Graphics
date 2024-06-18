#pragma once
#include <iostream>

namespace Utility
{
	const unsigned DEFAULT_SIZE = 0;
	const unsigned DEFAULT_CAPACITY = 8;

	//MyString
	const char TERMINATE_SYMBOL = '\0';
	unsigned nextPowerOfTwo(unsigned n);

	//BitSet
	const unsigned DEFAULT_BITS_PER_NUMBER = 1;
	const unsigned MIN_BITS_PER_NUMBER = 1;
	const unsigned MAX_BITS_PER_NUMBER = 8;
	const unsigned DEFAULT_MAX_NUMBER_IN_SET = 7;
	const unsigned BITS_IN_BYTE = 8;

	bool getBit(uint8_t num, unsigned pos);
	void setBit(uint8_t& num, unsigned pos, bool value);

	//NetPbm
	const char DEFAULT_MAGIC_NUMBER = '0';
	const unsigned DEFAULT_WIDTH = 0;
	const unsigned DEFAULT_HEIGHT = 0;

	//Color
	const unsigned RED_POITION = 0;
	const unsigned BLUE_POSITION = 1;
	const unsigned GREEN_POSITION = 2;
}