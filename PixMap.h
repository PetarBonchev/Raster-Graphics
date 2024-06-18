#pragma once
#include "NetPbm.h"
#include "Color.h"

class PixMap : public NetPbm
{
public:
	PixMap() = default;
	PixMap(const NetPbm base, Vector<Color> data) :NetPbm(base), data(data) {}
	PixMap(char magicNumber, unsigned width, unsigned height, Vector<MyString> header, Vector<Color> data) : NetPbm(magicNumber, width, height, header), data(data) {}
	~PixMap() = default;

	bool isValid() const override;

	NetPbm* clone()const override;

	void TurnTo(const NetPbm* other)override;

	void TurnToBitMap(const BitMap* other)override;
	void TurnToGrayMap(const GrayMap* other)override;
	void TurnToPixMap(const PixMap* other)override;

private:
	Vector<Color> data;
};