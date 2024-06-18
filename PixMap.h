#pragma once
#include "NetPbm.h"
#include "Color.h"

class PixMap : public NetPbm
{
public:
	PixMap() = default;
	PixMap(char magicNumber, unsigned width, unsigned height,const Vector<MyString> &header, unsigned colorValue,const Vector<Vector<Color>> &data);
	~PixMap() = default;

	bool isValid() const override;

	NetPbm* clone()const override;

	void TurnTo(NetPbm* other)override;

	void TurnToBitMap(BitMap* other)override;
	void TurnToGrayMap(GrayMap* other)override;
	void TurnToPixMap(PixMap* other)override;

private:
	unsigned colorValue = Utility::DEFAULT_MAX_COLOR_VALUE;
	Vector<Vector<Color>> data;
};