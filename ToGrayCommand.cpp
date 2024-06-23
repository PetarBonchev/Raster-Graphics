#include "ToGrayCommand.h"

ToGrayCommand::ToGrayCommand(Vector<Polymorphic_Ptr<NetPbm>>& data) : CommandVector(data) {}

void ToGrayCommand::execute()
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
			break;
		case Utility::PIXMAP_NORMAL_MAGIC_NUMBER:
		case Utility::PIXMAP_BINARY_MAGIC_NUMBER:
			data[i] = PixMapToGray(i);
			if (!data[i]->isValid())
				throw std::logic_error("converting pixmap to graymap error");
			break;
		default:
			throw std::logic_error("converting to graymap error");
			break;
		}
	}
}

void ToGrayCommand::undo()
{
}

CommandVector* ToGrayCommand::clone() const
{
	return new ToGrayCommand(*this);
}

MyString ToGrayCommand::message() const
{
	return MyString("grayscale");
}

NetPbm* ToGrayCommand::PixMapToGray(unsigned idx)
{
	PixMap* pixMap = (PixMap*)data[idx].get();

	if (!pixMap->isValid())
		throw std::logic_error("converting pixmap to graymap error");
	
	Vector<Vector<Color>> data = pixMap->getData();
	Vector<BitSet> newData;

	for (unsigned i = 0;i < data.getSize();i++)
	{
		BitSet newRow(data[i].getSize() - 1, Utility::minimumBitsToStore(pixMap->getColorValue()));
		for (unsigned j = 0;j < data[i].getSize();j++)
		{
			unsigned grayValue = data[i][j].r() * Utility::GRAYMAP_RED_TO_GRAY +
				data[i][j].g() * Utility::GRAYMAP_GREEN_TO_GRAY +
				data[i][j].b() * Utility::GRAYMAP_BLUE_TO_GRAY;
			newRow.setNumber(j, grayValue);
		}
		newData.pushBack(newRow);
	}

	char newMagicNumber = pixMap->getMagicNumber() == Utility::PIXMAP_NORMAL_MAGIC_NUMBER ?
		Utility::GRAYMAP_NORMAL_MAGIC_NUMBER : Utility::GRAYMAP_BINARY_MAGIC_NUMBER;

	return new GrayMap(newMagicNumber, pixMap->getWidth(), pixMap->getHeight(), pixMap->getHeader(), pixMap->getFilename(), pixMap->getColorValue(), newData);
}
