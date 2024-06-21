#pragma once
#include "NetPbm.h"

class BitMap : public NetPbm
{
public:
	BitMap() = default;
	BitMap(char magicNumber, unsigned width, unsigned height,const Vector<MyString> &header,const Vector<BitSet>& data);
	~BitMap() = default;

	bool isValid() const override;
	void negative() override;

	const Vector<BitSet>& getData()const;

private:
	Vector<BitSet> data;
};