#include "PixMap.h"

PixMap::PixMap(char magicNumber, unsigned width, unsigned height,const Vector<MyString> &header, const MyString& filename, unsigned colorValue,const Vector<Vector<Color>> &data)
	: NetPbm(magicNumber, width, height, header, filename), colorValue(colorValue), data(data) {}

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

void PixMap::rotate(bool left)
{
	std::swap(width, height);
	if (left)
		rotateLeft();
	else
		rotateRight();
}

void PixMap::negative()
{
	for (unsigned i = 0;i < data.getSize();i++)
	{
		for (unsigned j = 0;j < data[i].getSize();j++)
		{
			data[i][j].negative(colorValue);
		}
	}
}

const unsigned PixMap::getColorValue() const
{
	return colorValue;
}

const Vector<Vector<Color>>& PixMap::getData() const
{
	return data;
}

void PixMap::rotateLeft()
{
	unsigned rows = data[0].getSize();
	unsigned cols = data.getSize();

	Vector<Vector<Color>> newData;
	for (unsigned i = 0;i < rows;i++)
	{
		Vector<Color> newRow;
		for (unsigned j = 0;j < cols;j++)
		{
			BitSet newData(Utility::NUMBER_OF_COLORS_IN_PIXEL, colorValue);
			newData.setNumber(Utility::RED_POSITION, data[j][rows - i - 1].r());
			newData.setNumber(Utility::GREEN_POSITION, data[j][rows - i - 1].g());
			newData.setNumber(Utility::BLUE_POSITION, data[j][rows - i - 1].b());
			Color newColor(newData);
			newRow.pushBack(newColor);
		}
		newData.pushBack(newRow);
	}

	data = newData;
}

void PixMap::rotateRight()
{
	unsigned rows = data[0].getSize();
	unsigned cols = data.getSize();

	Vector<Vector<Color>> newData;
	for (unsigned i = 0;i < rows;i++)
	{
		Vector<Color> newRow;
		for (unsigned j = 0;j < cols;j++)
		{
			BitSet newData(Utility::NUMBER_OF_COLORS_IN_PIXEL, colorValue);
			newData.setNumber(Utility::RED_POSITION, data[cols - j - 1][i].r());
			newData.setNumber(Utility::GREEN_POSITION, data[cols - j - 1][i].g());
			newData.setNumber(Utility::BLUE_POSITION, data[cols - j - 1][i].b());
			Color newColor(newData);
			newRow.pushBack(newColor);
		}
		newData.pushBack(newRow);
	}

	data = newData;
}