#include "GrayMap.h"

GrayMap::GrayMap(char magicNumber, unsigned width, unsigned height, const Vector<MyString> &header, const MyString& filename, unsigned maxGray,const Vector<BitSet> &data)
	: NetPbm(magicNumber, width, height, header, filename), maxGray(maxGray), data(data) {}

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

void GrayMap::negative()
{
	for (unsigned i = 0;i < data.getSize();i++)
	{
		for (unsigned j = 0;j <= data[i].getMaxNumber();j++)
		{
			unsigned newValue = maxGray - data[i].getNumber(j);
			data[i].setNumber(j, newValue);
		}
	}
}

void GrayMap::rotate(bool left)
{
	std::swap(width, height);
	if (left)
		rotateLeft();
	else
		rotateRight();
}

void GrayMap::rotateLeft()
{
	unsigned rows = data[0].getMaxNumber() + 1;
	unsigned cols = data.getSize();

	Vector<BitSet> newData;
	for (unsigned i = 0;i < rows;i++)
	{
		BitSet newRow(cols - 1, maxGray);
		for (unsigned j = 0;j < cols;j++)
		{
			newRow.setNumber(j, data[j].getNumber(rows - i - 1));
		}
		newData.pushBack(newRow);
	}

	data = newData;
}

void GrayMap::rotateRight()
{
	unsigned rows = data[0].getMaxNumber() + 1;
	unsigned cols = data.getSize();

	Vector<BitSet> newData;
	for (unsigned i = 0;i < rows;i++)
	{
		BitSet newRow(cols - 1, maxGray);
		for (unsigned j = 0;j < cols;j++)
		{
			newRow.setNumber(j, data[cols - j - 1].getNumber(i));
		}
		newData.pushBack(newRow);
	}

	data = newData;
}

const unsigned GrayMap::getMaxGray() const
{
	return maxGray;
}

const Vector<BitSet>& GrayMap::getData() const
{
	return data;
}
