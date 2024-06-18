#include "GrayMap.h"

GrayMap::GrayMap(char magicNumber, unsigned width, unsigned height, Vector<MyString> header, unsigned maxGray, Vector<BitSet> data)
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

NetPbm* GrayMap::clone() const
{
	return new GrayMap(*this);
}

void GrayMap::TurnTo(NetPbm* other)
{
	other->TurnToGrayMap(this);
}

void GrayMap::TurnToBitMap(BitMap* other)
{
}

void GrayMap::TurnToGrayMap(GrayMap* other)
{
}

void GrayMap::TurnToPixMap(PixMap* other)
{
}
