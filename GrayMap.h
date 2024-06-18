#pragma once
#include "NetPbm.h"

class GrayMap : public NetPbm
{
public:
	GrayMap() = default;
	GrayMap(char magicNumber, unsigned width, unsigned height, const Vector<MyString> &header, unsigned maxGray,const Vector<BitSet> &data);
	~GrayMap() = default;

	bool isValid() const override;

	NetPbm* clone()const override;

	void TurnTo(NetPbm* other)override;

	void TurnToBitMap(BitMap* other)override;
	void TurnToGrayMap(GrayMap* other)override;
	void TurnToPixMap(PixMap* other)override;

//private:
	unsigned maxGray = Utility::DEFAULT_MAX_GRAY_VALUE;
	Vector<BitSet> data;
};