#pragma once
#include <iostream>

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

	void add(unsigned number);
	void remove(unsigned number);

	unsigned getNumber(unsigned number)const;

	void printMem()const;

private:

	void free();
	void copyFrom(const BitSet& other);
	void moveFrom(BitSet&& other)noexcept;

	uint8_t* container = nullptr;
	unsigned size = 0;
	unsigned capacity = 0;
	const unsigned bitsPerNumber = 1;
};

bool getBit(uint8_t num, unsigned pos);
void setBit(uint8_t& num, unsigned pos, bool value);