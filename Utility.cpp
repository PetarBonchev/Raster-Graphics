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