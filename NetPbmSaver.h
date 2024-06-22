#pragma once
#include "BitMap.h"
#include "GrayMap.h"
#include "PixMap.h"

class NetPbmSaver
{
public:
	static void savePbm(const NetPbm* object);

private:

	static void saveP1(const BitMap* object);
	static void saveP2(const GrayMap* object);
	static void saveP3(const PixMap* object);
	static void saveP4(const BitMap* object);
	static void saveP5(const GrayMap* object);
	static void saveP6(const PixMap* object);

};
