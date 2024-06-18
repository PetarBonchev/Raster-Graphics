#include "BitMap.h"

BitMap::BitMap(char magicNumber, unsigned width, unsigned height, const Vector<MyString> &header, const Vector<BitSet> &data) : NetPbm(magicNumber, width, height, header), data(data) {}

bool BitMap::isValid() const
{
	if (magicNumber != Utility::BITMAP_NORMAL_MAGIC_NUMBER && magicNumber != Utility::BITMAP_BINARY_MAGIC_NUMBER)
		return false;

	if (width * height == 0)
		return false;

	if (data.getSize() != height)
		return false;

	if (data[0].getMaxNumber() + 1 != width)
		return false;

	return true;
}

NetPbm* BitMap::clone() const
{
	return new BitMap(*this);
}

void BitMap::TurnTo(NetPbm* other)
{
	other->TurnToBitMap(this);
}

void BitMap::TurnToBitMap(BitMap* other)
{
}

void BitMap::TurnToGrayMap(GrayMap* other)
{
}

void BitMap::TurnToPixMap(PixMap* other)
{
}
