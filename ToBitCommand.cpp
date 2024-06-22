#include "ToBitCommand.h"

ToBitCommand::ToBitCommand(Vector<Polymorphic_Ptr<NetPbm>>& data) : CommandVector(data) {}

void ToBitCommand::execute()
{
	for (unsigned i = 0;i < data.getSize();i++)
	{
		switch (data[i]->getMagicNumber())
		{
		case Utility::BITMAP_NORMAL_MAGIC_NUMBER:
		case Utility::BITMAP_BINARY_MAGIC_NUMBER:
			break;
		case Utility::GRAYMAP_NORMAL_MAGIC_NUMBER:
		case Utility::GRAYMAP_BINARY_MAGIC_NUMBER:
			data[i] = GrayMapToBit(i);
			if (!data[i]->isValid())
				throw std::logic_error("converting graymap to bitmap error");
			break;
		case Utility::PIXMAP_NORMAL_MAGIC_NUMBER:
		case Utility::PIXMAP_BINARY_MAGIC_NUMBER:
			data[i] = PixMapToBit(i);
			if (!data[i]->isValid())
				throw std::logic_error("converting pixmap to bitmap error");
			break;
		default:
			throw std::logic_error("converting to bitmap error");
			break;
		}
	}
}

void ToBitCommand::undo()
{
}

CommandVector* ToBitCommand::clone() const
{
	return new ToBitCommand(*this);
}

NetPbm* ToBitCommand::GrayMapToBit(unsigned idx)
{
	GrayMap* grayMap = (GrayMap*)data[idx].get();

	if (!grayMap->isValid())
		throw std::logic_error("converting graymap to bitmap error");

	Vector<BitSet> data = grayMap->getData();
	Vector<BitSet> newData;

	for (unsigned i = 0;i < data.getSize();i++)
	{
		BitSet newRow(data[i].getMaxNumber(), Utility::DEFAULT_MAX_BIT_VALUE);
		for (unsigned j = 0;j <= data[i].getMaxNumber();j++)
		{
			unsigned newValue = data[i].getNumber(j) >= Utility::GRAYMAP_BITMAP_WHITE_COLOR_TRESHOLD ?
				Utility::BITMAP_WHITE_COLOR_VALUE : Utility::BITMAP_BLACK_COLOR_VALUE;
			newRow.setNumber(j, newValue);
		}
		newData.pushBack(newRow);
	}

	char newMagicNumber = grayMap->getMagicNumber() == Utility::GRAYMAP_NORMAL_MAGIC_NUMBER ? 
		Utility::BITMAP_NORMAL_MAGIC_NUMBER : Utility::BITMAP_BINARY_MAGIC_NUMBER;
	
	return new BitMap(newMagicNumber, grayMap->getWidth(), grayMap->getHeight(), grayMap->getHeader(), grayMap->getFilename(), newData);
}

NetPbm* ToBitCommand::PixMapToBit(unsigned idx)
{
	PixMap* pixMap = (PixMap*)data[idx].get();

	if (!pixMap->isValid())
		throw std::logic_error("converting pixmap to bitmap error");

	Vector<Vector<Color>> data = pixMap->getData();
	Vector<BitSet> newData;

	for (unsigned i = 0;i < data.getSize();i++)
	{
		BitSet newRow(data[i].getSize() - 1, Utility::DEFAULT_MAX_BIT_VALUE);
		for (unsigned j = 0;j < data[i].getSize();j++)
		{
			unsigned grayValue = data[i][j].r() * Utility::GRAYMAP_RED_TO_GRAY +
								 data[i][j].g() * Utility::GRAYMAP_GREEN_TO_GRAY +
								 data[i][j].b() * Utility::GRAYMAP_BLUE_TO_GRAY;
			unsigned newValue = grayValue >= Utility::GRAYMAP_BITMAP_WHITE_COLOR_TRESHOLD ?
				Utility::BITMAP_WHITE_COLOR_VALUE : Utility::BITMAP_BLACK_COLOR_VALUE;
			newRow.setNumber(j, newValue);
		}
		newData.pushBack(newRow);
	}

	char newMagicNumber = pixMap->getMagicNumber() == Utility::GRAYMAP_NORMAL_MAGIC_NUMBER ?
		Utility::BITMAP_NORMAL_MAGIC_NUMBER : Utility::BITMAP_BINARY_MAGIC_NUMBER;

	return new BitMap(newMagicNumber, pixMap->getWidth(), pixMap->getHeight(), pixMap->getHeader(), pixMap->getFilename(), newData);
}
