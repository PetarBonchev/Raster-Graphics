#pragma once
#include "BitSet.h"

class Color
{
public:
	Color() = default;
	Color(const BitSet& bitData);
	Color(unsigned r, unsigned g, unsigned b, unsigned maxValue);

	unsigned r()const;
	unsigned g()const;
	unsigned b()const;

	void negative(unsigned maxValue);
private:
	void check()const;
	BitSet data;
};