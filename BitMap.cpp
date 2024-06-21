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

const Vector<BitSet>& BitMap::getData() const
{
	return data;
}
