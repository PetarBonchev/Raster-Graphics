#pragma once
#include "NetPbm.h"

class GrayMap : public NetPbm
{
public:
	GrayMap() = default;
	GrayMap(char magicNumber, unsigned width, unsigned height, const Vector<MyString> &header, unsigned maxGray,const Vector<BitSet> &data);
	~GrayMap() = default;

	bool isValid() const override;
	void negative() override;

	const unsigned getMaxGray()const;
	const Vector<BitSet>& getData()const;

private:
	unsigned maxGray = Utility::DEFAULT_MAX_GRAY_VALUE;
	Vector<BitSet> data;
};