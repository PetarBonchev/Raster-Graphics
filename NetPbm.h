#pragma once
#include "Vector.hpp"
#include "MyString.h"
#include "BitSet.h"
#include "Utility.h"

class BitMap;
class GrayMap;
class PixMap;

class NetPbm
{
public:
	NetPbm() = default;
	NetPbm(char magicNumber, unsigned width, unsigned height, Vector<MyString> header) :magicNumber(magicNumber), width(width), height(height), header(header) {}

	virtual NetPbm* clone()const = 0;

	virtual void TurnTo(const NetPbm* other) const = 0;

	virtual void TurnToBitMap(const BitMap* other) const = 0;
	virtual void TurnToGrayMap(const GrayMap* other)const = 0;
	virtual void TurnToPixMap(const PixMap* other)const = 0;

	virtual ~NetPbm() = default;
private:

	char magicNumber = Utility::DEFAULT_MAGIC_NUMBER;
	unsigned width = Utility::DEFAULT_WIDTH;
	unsigned height = Utility::DEFAULT_HEIGHT;
	Vector<MyString> header;
};