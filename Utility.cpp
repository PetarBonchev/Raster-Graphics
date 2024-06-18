#include "Utility.h"

unsigned Utility::nextPowerOfTwo(unsigned n)
{
	unsigned step = 1;

	while ((n >> step) > 0) {
		n |= n >> step;
		step <<= 1;
	}

	return n + 1;
}

bool Utility::getBit(uint8_t num, unsigned pos)
{
	if (pos >= 8)
		throw std::logic_error("bit does not exist");

	uint8_t mask = 1 << pos;

	return (num & mask);
}

void Utility::setBit(uint8_t& num, unsigned pos, bool value)
{
	if (pos >= 8)
		throw std::logic_error("bit does not exist");

	uint8_t mask = 1 << pos;

	if (value)
	{
		num |= mask;
	}
	else
	{
		mask = ~mask;
		num &= mask;
	}
}

bool Utility::isDigit(char ch)
{
	return '0' <= ch && ch <= '9';
}

unsigned Utility::charToDigit(char ch)
{
	if (!isDigit(ch))
		throw std::logic_error("incorrect input - text to number failed");

	return ch - '0';
}

bool Utility::isBit(unsigned number)
{
	return number == 0 || number == 1;
}

unsigned Utility::minimumBitsToStore(unsigned number)
{
	unsigned ans = 0;
	while (number)
	{
		number >>= 1;
		ans++;
	}
	return ans;
}


