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

	//BitMap
	const char BITMAP_NORMAL_MAGIC_NUMBER = '1';
	const char BITMAP_BINARY_MAGIC_NUMBER = '4';

	//GrayMap
	const unsigned DEFAULT_MAX_GRAY_VALUE = 15;
	const char GRAYMAP_NORMAL_MAGIC_NUMBER = '2';
	const char GRAYMAP_BINARY_MAGIC_NUMBER = '5';

	//PixMap
	const unsigned DEFAULT_MAX_COLOR_VALUE = 255;
	const char PIXMAP_NORMAL_MAGIC_NUMBER = '3';
	const char PIXMAP_BINARY_MAGIC_NUMBER = '6';
}