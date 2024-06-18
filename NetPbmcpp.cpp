#include "NetPbm.h"

NetPbm::NetPbm(char magicNumber, unsigned width, unsigned height, Vector<MyString> header) :magicNumber(magicNumber), width(width), height(height), header(header) {}

bool NetPbm::isValid() const
{
	return false;
}