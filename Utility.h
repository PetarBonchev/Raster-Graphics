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
	const unsigned DEFAULT_MAX_BIT_VALUE = 1;
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
	const unsigned NUMBER_OF_COLORS_IN_PIXEL = 3;

	//NetPbmCreator
	const unsigned BUFFER_SIZE = 1024;
	const unsigned MAGIC_NUMBER_POSITION_ON_ROW_1 = 1;
	const char COMMENT_SIGN = '#';
	const char NUMBER_SEPARATOR = ' ';
	bool isDigit(char ch);
	unsigned charToDigit(char ch);
	bool isBit(unsigned number);
	unsigned minimumBitsToStore(unsigned number);

	const unsigned EXPECTED_NUMBERS_BITMAP = 2;
	const unsigned EXPECTED_NUMBERS_OTHERS = 3;
}