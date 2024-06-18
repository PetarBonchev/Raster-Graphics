#pragma once
#include <fstream>

#include "BitMap.h"
#include "GrayMap.h"
#include "PixMap.h"

class NetPbmCreator
{
public:
	static NetPbm* readPbm(const MyString& filename);

	static NetPbm* readBitMap(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header);
	static NetPbm* readGrayMap(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header, unsigned maxGray);
	static NetPbm* readPixMap(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header, unsigned colorValue);
	static NetPbm* readBitMapBinary(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header);
	static NetPbm* readGrayMapBinary(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header, unsigned maxGray);
	static NetPbm* readPixMapBinary(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header, unsigned colorValue);
};

Vector<unsigned> strToVector(const MyString& str);
unsigned characterCount(const Vector<MyString>& text);