#include "BitSet.h"

BitSet::BitSet() :BitSet(7, 1)
{
}

BitSet::BitSet(unsigned maxNumber, unsigned bits) : bitsPerNumber(bits)
{
	if (bits == 0 || bits > 8)
		throw std::logic_error("invalid bit count");

	size = maxNumber;
	capacity = (size + 1) * bits;
	if (capacity % 8)
		capacity += 8 - capacity % 8;

	container = new uint8_t[capacity / 8]{};
}

BitSet::BitSet(const BitSet& other)
{
	copyFrom(other);
}

BitSet::BitSet(BitSet&& other) noexcept
{
	moveFrom(std::move(other));
}

BitSet& BitSet::operator=(const BitSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

BitSet& BitSet::operator=(BitSet&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

BitSet::~BitSet()
{
	free();
}

void BitSet::add(unsigned number)
{
	if (number > size)
		throw std::out_of_range("set does not contain the number");

	unsigned idx = (number + 1) * bitsPerNumber - 1;

	for (unsigned i = 0; i < bitsPerNumber; i++, idx--)
	{
		if (getBit(container[idx / 8], idx % 8))
		{
			setBit(container[idx / 8], idx % 8, false);
		}
		else
		{
			setBit(container[idx / 8], idx % 8, true);
			break;
		}
	}
}

void BitSet::remove(unsigned number)
{
	if (number > size)
		throw std::out_of_range("set does not contain the number");

	unsigned idx = (number + 1) * bitsPerNumber - 1;

	for (unsigned i = 0; i < bitsPerNumber; i++, idx--)
	{
		if (getBit(container[idx / 8], idx % 8))
		{
			setBit(container[idx / 8], idx % 8, false);
			break;
		}
		else
		{
			setBit(container[idx / 8], idx % 8, true);
		}
	}
}

unsigned BitSet::getNumber(unsigned number) const
{
	if (number > size)
		throw std::out_of_range("set does not contain the number");

	unsigned idx = number * bitsPerNumber;
	unsigned ret = 0;

	for (unsigned i = 0; i < bitsPerNumber; i++, idx++)
	{
		ret <<= 1;
		ret += getBit(container[idx / 8], idx % 8);
	}

	return ret;
}

void BitSet::printMem() const
{
	unsigned bits = (size + 1) * bitsPerNumber;
	std::cout << bits << std::endl;

	for (unsigned i = 0; i < bits; i++)
	{
		if (!(i % 8))std::cout << " ";
		std::cout << getBit(container[i / 8], i % 8);
	}

	std::cout << std::endl;
}

void BitSet::free()
{
	delete[] container;
	size = 0;
	capacity = 0;
}

void BitSet::copyFrom(const BitSet& other)
{
	capacity = other.capacity;
	size = other.size;
	container = new uint8_t[capacity / 8]{};
}

void BitSet::moveFrom(BitSet&& other) noexcept
{
	capacity = other.capacity;
	other.capacity = 0;

	size = other.size;
	other.size = 0;

	container = other.container;
	other.container = nullptr;
}

bool getBit(uint8_t num, unsigned pos)
{
	if (pos >= 8)
		throw std::logic_error("bit does not exist");

	uint8_t mask = 1 << pos;

	return (num & mask);
}

void setBit(uint8_t& num, unsigned pos, bool value)
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
