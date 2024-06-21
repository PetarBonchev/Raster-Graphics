#pragma once
#include "Vector.hpp"
#include "MyString.h"
#include "BitSet.h"
#include "Utility.h"

class NetPbm
{
public:
	NetPbm() = default;
	NetPbm(char magicNumber, unsigned width, unsigned height, Vector<MyString> header);

	virtual bool isValid() const;
	virtual void negative() = 0;

	const char getMagicNumber()const;
	const unsigned getWidth()const;
	const unsigned getHeight()const;
	const Vector<MyString>& getHeader()const;

	virtual ~NetPbm() = default;
protected:

	char magicNumber = Utility::DEFAULT_MAGIC_NUMBER;
	unsigned width = Utility::DEFAULT_WIDTH;
	unsigned height = Utility::DEFAULT_HEIGHT;
	Vector<MyString> header;
};