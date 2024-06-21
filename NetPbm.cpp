#include "NetPbm.h"

NetPbm::NetPbm(char magicNumber, unsigned width, unsigned height, Vector<MyString> header) :magicNumber(magicNumber), width(width), height(height), header(header) {}

bool NetPbm::isValid() const
{
	return false;
}

const char NetPbm::getMagicNumber() const
{
	return magicNumber;
}

const unsigned NetPbm::getWidth() const
{
	return width;
}

const unsigned NetPbm::getHeight() const
{
	return height;
}

const Vector<MyString>& NetPbm::getHeader() const
{
	return header;
}
