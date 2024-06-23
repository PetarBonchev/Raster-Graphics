#include "BitMap.h"

BitMap::BitMap(char magicNumber, unsigned width, unsigned height, const Vector<MyString> &header, const MyString& filename, const Vector<BitSet> &data) 
	: NetPbm(magicNumber, width, height, header, filename), data(data) {}

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

void BitMap::negative()
{
	for (unsigned i = 0;i < data.getSize();i++)
	{
		for (unsigned j = 0;j <= data[i].getMaxNumber();j++)
		{
			unsigned newValue = Utility::DEFAULT_MAX_BIT_VALUE - data[i].getNumber(j);
			data[i].setNumber(j, newValue);
		}
	}
}

void BitMap::rotate(bool left)
{
	std::swap(width, height);
	if (left)
		rotateLeft();
	else
		rotateRight();
}

NetPbm* BitMap::clone() const
{
	return new BitMap(*this);
}

const Vector<BitSet>& BitMap::getData() const
{
	return data;
}

void BitMap::rotateLeft()
{
	unsigned rows = data[0].getMaxNumber() + 1;
	unsigned cols = data.getSize();

	Vector<BitSet> newData;
	for (unsigned i = 0;i < rows;i++)
	{
		BitSet newRow(cols - 1, Utility::DEFAULT_MAX_BIT_VALUE);
		for (unsigned j = 0;j < cols;j++)
		{
			newRow.setNumber(j, data[j].getNumber(rows - i - 1));
		}
		newData.pushBack(newRow);
	}

	data = newData;

	height = rows;
	width = cols;
}

void BitMap::rotateRight()
{
	unsigned rows = data[0].getMaxNumber() + 1;
	unsigned cols = data.getSize();

	Vector<BitSet> newData;
	for (unsigned i = 0;i < rows;i++)
	{
		BitSet newRow(cols - 1, Utility::DEFAULT_MAX_BIT_VALUE);
		for (unsigned j = 0;j < cols;j++)
		{
			newRow.setNumber(j, data[cols - j - 1].getNumber(i));
		}
		newData.pushBack(newRow);
	}

	data = newData;

	height = rows;
	width = cols;
}
/*
11 12 13 14
21 22 23 24
31 32 33 34

rows = 4
cols = 3

14 24 34
13 23 33
12 22 32
11 21 31

31 21 11
32 22 12
33 23 13
34 24 14
*/