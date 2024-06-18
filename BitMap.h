#pragma once
#include "NetPbm.h"

class BitMap : public NetPbm
{
public:
	BitMap() = default;
	BitMap(const NetPbm base, Vector<BitSet> data) :NetPbm(base), data(data) {}
	BitMap(char magicNumber, unsigned width, unsigned height, Vector<MyString> header, Vector<BitSet> data) : NetPbm(magicNumber, width, height, header), data(data) {}
	~BitMap() = default;

	bool isValid() const override;

	NetPbm* clone()const override;

	void TurnTo(const NetPbm* other)override;

	void TurnToBitMap(const BitMap* other)override;
	void TurnToGrayMap(const GrayMap* other)override;
	void TurnToPixMap(const PixMap* other)override;

private:
	Vector<BitSet> data;
};