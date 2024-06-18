#pragma once
#include <iostream>
#include "Utility.h"

class BitSet
{
public:
	BitSet();
	BitSet(unsigned maxNumber, unsigned bits);
	BitSet(const BitSet& other);
	BitSet(BitSet&& other)noexcept;
	BitSet& operator=(const BitSet& other);
	BitSet& operator=(BitSet&& other)noexcept;
	~BitSet();

	unsigned getMaxNumber()const;

	void add(unsigned number);
	void remove(unsigned number);

	unsigned getNumber(unsigned number)const;
	void setNumber(unsigned number, unsigned value);

	void printMem()const;

private:

	void free();
	void copyFrom(const BitSet& other);
	void moveFrom(BitSet&& other)noexcept;

	uint8_t* container = nullptr;
	unsigned size = Utility::DEFAULT_SIZE;
	unsigned capacity = Utility::DEFAULT_CAPACITY;
	const unsigned bitsPerNumber = Utility::DEFAULT_BITS_PER_NUMBER;
};