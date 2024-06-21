#include "GrayMap.h"

GrayMap::GrayMap(char magicNumber, unsigned width, unsigned height, const Vector<MyString> &header, unsigned maxGray,const Vector<BitSet> &data)
	: NetPbm(magicNumber, width, height, header), maxGray(maxGray), data(data) {}

bool GrayMap::isValid() const
{
	if (magicNumber != Utility::GRAYMAP_NORMAL_MAGIC_NUMBER && magicNumber != Utility::GRAYMAP_BINARY_MAGIC_NUMBER)
		return false;

	if (width * height == 0)
		return false;

	if (data.getSize() != height)
		return false;

	if (data[0].getMaxNumber() + 1 != width)
		return false;

	if (maxGray == 0)
		return false;

	return true;
}

const unsigned GrayMap::getMaxGray() const
{
	return maxGray;
}

const Vector<BitSet>& GrayMap::getData() const
{
	return data;
}
