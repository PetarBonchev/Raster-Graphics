#pragma once
#include "NetPbm.h"

class BitMap : public NetPbm
{
public:
	BitMap() = default;
	BitMap(char magicNumber, unsigned width, unsigned height,const Vector<MyString> &header,const Vector<BitSet>& data);
	~BitMap() = default;

	bool isValid() const override;

	NetPbm* clone()const override;

	void TurnTo(NetPbm* other)override;

	void TurnToBitMap(BitMap* other)override;
	void TurnToGrayMap(GrayMap* other)override;
	void TurnToPixMap(PixMap* other)override;

//private:
	Vector<BitSet> data;
};