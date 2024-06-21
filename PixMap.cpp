#include "PixMap.h"

PixMap::PixMap(char magicNumber, unsigned width, unsigned height,const Vector<MyString> &header, unsigned colorValue,const Vector<Vector<Color>> &data)
	: NetPbm(magicNumber, width, height, header), colorValue(colorValue), data(data) {}

bool PixMap::isValid() const
{
	if (magicNumber != Utility::PIXMAP_NORMAL_MAGIC_NUMBER && magicNumber != Utility::PIXMAP_BINARY_MAGIC_NUMBER)
		return false;

	if (width * height == 0)
		return false;

	if (data.getSize() != height)
		return false;

	if (data[0].getSize() != width)
		return false;

	if (colorValue == 0)
		return false;

	return true;
}

const unsigned PixMap::getColorValue() const
{
	return colorValue;
}

const Vector<Vector<Color>>& PixMap::getData() const
{
	return data;
}