#pragma once
#include "NetPbm.h"

class GrayMap : public NetPbm
{
public:
	GrayMap() = default;
	GrayMap(const NetPbm base, Vector<BitSet> data) :NetPbm(base), data(data) {}
	GrayMap(char magicNumber, unsigned width, unsigned height, Vector<MyString> header, Vector<BitSet> data) : NetPbm(magicNumber, width, height, header), data(data) {}
	~GrayMap() = default;

	bool isValid() const override;

	NetPbm* clone()const override;

	void TurnTo(const NetPbm* other)override;

	void TurnToBitMap(const BitMap* other)override;
	void TurnToGrayMap(const GrayMap* other)override;
	void TurnToPixMap(const PixMap* other)override;

private:
	Vector<BitSet> data;
};