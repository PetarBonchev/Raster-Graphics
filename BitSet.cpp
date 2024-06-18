#include "BitSet.h"

BitSet::BitSet() :BitSet(Utility::DEFAULT_MAX_NUMBER_IN_SET, Utility::DEFAULT_BITS_PER_NUMBER)
{
}

BitSet::BitSet(unsigned maxNumber, unsigned bits) : bitsPerNumber(bits)
{
	if (bits < Utility::MIN_BITS_PER_NUMBER || bits > Utility::MAX_BITS_PER_NUMBER)
		throw std::logic_error("invalid bit count");

	size = maxNumber;
	capacity = (size + 1) * bits; // 0
	if (capacity % Utility::BITS_IN_BYTE)
		capacity += Utility::BITS_IN_BYTE - capacity % Utility::BITS_IN_BYTE;

	container = new uint8_t[capacity / Utility::BITS_IN_BYTE]{};
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

unsigned BitSet::getMaxNumber() const
{
	return size;
}

void BitSet::add(unsigned number)
{
	if (number > size)
		throw std::out_of_range("set does not contain the number");

	unsigned idx = (number + 1) * bitsPerNumber - 1;//0

	for (unsigned i = 0; i < bitsPerNumber; i++, idx--)
	{
		if (Utility::getBit(container[idx / Utility::BITS_IN_BYTE], idx % Utility::BITS_IN_BYTE))
		{
			Utility::setBit(container[idx / Utility::BITS_IN_BYTE], idx % Utility::BITS_IN_BYTE, false);
		}
		else
		{
			Utility::setBit(container[idx / Utility::BITS_IN_BYTE], idx % Utility::BITS_IN_BYTE, true);
			break;
		}
	}
}

void BitSet::remove(unsigned number)
{
	if (number > size)
		throw std::out_of_range("set does not contain the number");

	unsigned idx = (number + 1) * bitsPerNumber - 1;//0

	for (unsigned i = 0; i < bitsPerNumber; i++, idx--)
	{
		if (Utility::getBit(container[idx / Utility::BITS_IN_BYTE], idx % Utility::BITS_IN_BYTE))
		{
			Utility::setBit(container[idx / Utility::BITS_IN_BYTE], idx % Utility::BITS_IN_BYTE, false);
			break;
		}
		else
		{
			Utility::setBit(container[idx / Utility::BITS_IN_BYTE], idx % Utility::BITS_IN_BYTE, true);
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
		ret += Utility::getBit(container[idx / Utility::BITS_IN_BYTE], idx % Utility::BITS_IN_BYTE);
	}

	return ret;
}

void BitSet::setNumber(unsigned number, unsigned value)
{
	if (number > size)
		throw std::out_of_range("set does not contain the number");

	unsigned idx = (number + 1) * bitsPerNumber - 1;//0

	for (unsigned i = 0; i < bitsPerNumber; i++, idx--)
	{
		Utility::setBit(container[idx / Utility::BITS_IN_BYTE], idx % Utility::BITS_IN_BYTE, Utility::getBit(value, i));
	}
}

void BitSet::printMem() const
{
	unsigned bits = (size + 1) * bitsPerNumber;
	std::cout << bits << std::endl;

	for (unsigned i = 0; i < bits; i++)
	{
		if (!(i % 8))std::cout << " ";
		std::cout << Utility::getBit(container[i / Utility::BITS_IN_BYTE], i % Utility::BITS_IN_BYTE);
	}

	std::cout << std::endl;
}

void BitSet::free()
{
	delete[] container;
	size = Utility::DEFAULT_SIZE;
	capacity = Utility::DEFAULT_CAPACITY;
}

void BitSet::copyFrom(const BitSet& other)
{
	capacity = other.capacity;
	size = other.size;
	bitsPerNumber = other.bitsPerNumber;
	container = new uint8_t[capacity / Utility::BITS_IN_BYTE]{};

	for (unsigned i = 0; i <= size; i++)
	{
		setNumber(i, other.getNumber(i));
	}
}

void BitSet::moveFrom(BitSet&& other) noexcept
{
	capacity = other.capacity;
	other.capacity = 0;

	size = other.size;
	other.size = Utility::DEFAULT_SIZE;

	container = other.container;
	other.container = nullptr;
}

