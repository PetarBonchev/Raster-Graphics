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
	void negative() override;

	const unsigned getColorValue()const;
	const Vector<Vector<Color>>& getData()const;

private:
	unsigned colorValue = Utility::DEFAULT_MAX_COLOR_VALUE;
	Vector<Vector<Color>> data;
};