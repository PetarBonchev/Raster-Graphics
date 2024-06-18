#pragma once
#include "BitSet.h"

class Color
{
public:
	Color() = default;
	Color(BitSet data);
	Color(unsigned r, unsigned g, unsigned b, unsigned maxValue);

	unsigned r()const;
	unsigned g()const;
	unsigned b()const;
private:
	BitSet data;
};