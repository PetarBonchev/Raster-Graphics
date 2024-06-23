#include "CollageCommand.h"

CollageCommand::CollageCommand(Vector<Polymorphic_Ptr<NetPbm>>& data, unsigned img1Idx, unsigned img2Idx, 
	bool isHorizontal, const MyString& saveFileName) : CommandVector(data), img1Idx(img1Idx),img2Idx(img2Idx),
	isHorizontal(isHorizontal), saveFileName(saveFileName) {}

void CollageCommand::execute()
{
	NetPbm* obj1 = data[img1Idx].get();
	NetPbm* obj2 = data[img1Idx].get();

	if (obj1->getMagicNumber() != obj2->getMagicNumber())
		throw std::logic_error("images have different types");

	if (isHorizontal && (obj1->getHeight() != obj2->getHeight()))
		throw std::logic_error("images have different height");

	if (!isHorizontal && (obj1->getWidth() != obj2->getWidth()))
		throw std::logic_error("images have different width");

	NetPbm* newObj = nullptr;
	switch (obj1->getMagicNumber())
	{
	case Utility::BITMAP_NORMAL_MAGIC_NUMBER:
	case Utility::BITMAP_BINARY_MAGIC_NUMBER:
		if (!newObj->isValid())
			throw std::logic_error("colaging bitmap error");
		newObj = collageBitMaps(((BitMap*)(obj1)), ((BitMap*)(obj2)));
		break;
	case Utility::GRAYMAP_NORMAL_MAGIC_NUMBER:
	case Utility::GRAYMAP_BINARY_MAGIC_NUMBER:
		newObj = collageGrayMaps(((GrayMap*)(obj1)), ((GrayMap*)(obj2)));
		if (!newObj->isValid())
			throw std::logic_error("colaging graymaps error");
		break;
	case Utility::PIXMAP_NORMAL_MAGIC_NUMBER:
	case Utility::PIXMAP_BINARY_MAGIC_NUMBER:
		newObj = collagePixMaps(((PixMap*)(obj1)), ((PixMap*)(obj2)));
		if (!newObj->isValid())
			throw std::logic_error("colaging pixmaps error");
		break;
	default:
		throw std::logic_error("colaging error");
		break;
	}
}

void CollageCommand::undo()
{
}

CommandVector* CollageCommand::clone() const
{
	return new CollageCommand(*this);
}

MyString CollageCommand::message() const
{
	return MyString("collage");
}

NetPbm* CollageCommand::collageBitMaps(const BitMap* img1,const BitMap* img2)const
{
	unsigned newWidth = img1->getWidth();
	unsigned newHeight = img1->getHeight();
	if (isHorizontal)
		newWidth = img1->getWidth() + img2->getWidth();
	else
		newHeight = img1->getHeight() + img2->getHeight();

	Vector<MyString> header(img1->getHeader());
	for (unsigned i = 0;i < img2->getHeader().getSize();i++)
	{
		if (img2->getHeader()[i][0] == Utility::COMMENT_SIGN)
		{
			header.pushBack(img2->getHeader()[i]);
		}
	}

	char magicNumber = img1->getMagicNumber();
	Vector<BitSet> data;

	for (unsigned i = 0;i < newHeight;i++)
	{
		unsigned img1Size = img1->getData()[i].getMaxNumber();
		BitSet newRow(newHeight, 1);
		for (unsigned j = 0;j < newWidth;j++)
		{
			unsigned newData = 0;
			if (j > img1Size)
			{
				newData = img2->getData()[i].getNumber(j - img1Size - 1);
			}
			else if (i >= img1->getData().getSize())
			{
				newData = img2->getData()[i - img1->getData().getSize()].getNumber(j);
			}
			else newData = img1->getData()[i].getNumber(j);
			newRow.setNumber(j, newData);
		}
		data.pushBack(newRow);
	}

	return new BitMap(magicNumber, newWidth, newHeight, header, saveFileName, data);
}

NetPbm* CollageCommand::collageGrayMaps(const GrayMap* img1, const GrayMap* img2)const
{

	unsigned newWidth = img1->getWidth();
	unsigned newHeight = img1->getHeight();
	if (isHorizontal)
		newWidth = img1->getWidth() + img2->getWidth();
	else
		newHeight = img1->getHeight() + img2->getHeight();

	Vector<MyString> header(img1->getHeader());
	for (unsigned i = 0;i < img2->getHeader().getSize();i++)
	{
		if (img2->getHeader()[i][0] == Utility::COMMENT_SIGN)
		{
			header.pushBack(img2->getHeader()[i]);
		}
	}

	char magicNumber = img1->getMagicNumber();
	Vector<BitSet> data;

	for (unsigned i = 0;i < newHeight;i++)
	{
		unsigned img1Size = img1->getData()[i].getMaxNumber();
		BitSet newRow(newHeight, Utility::minimumBitsToStore(img1->getMaxGray()));
		for (unsigned j = 0;j < newWidth;j++)
		{
			unsigned newData = 0;
			if (j > img1Size)
			{
				newData = img2->getData()[i].getNumber(j - img1Size - 1);
			}
			else if (i >= img1->getData().getSize())
			{
				newData = img2->getData()[i - img1->getData().getSize()].getNumber(j);
			}
			else newData = img1->getData()[i].getNumber(j);
			newRow.setNumber(j, newData);
		}
		data.pushBack(newRow);
	}

	return new GrayMap(magicNumber, newWidth, newHeight, header, saveFileName, img1->getMaxGray(), data);
}

NetPbm* CollageCommand::collagePixMaps(const PixMap* img1, const PixMap* img2)const
{
	unsigned newWidth = img1->getWidth();
	unsigned newHeight = img1->getHeight();
	if (isHorizontal)
		newWidth = img1->getWidth() + img2->getWidth();
	else
		newHeight = img1->getHeight() + img2->getHeight();

	Vector<MyString> header(img1->getHeader());
	for (unsigned i = 0;i < img2->getHeader().getSize();i++)
	{
		if (img2->getHeader()[i][0] == Utility::COMMENT_SIGN)
		{
			header.pushBack(img2->getHeader()[i]);
		}
	}

	char magicNumber = img1->getMagicNumber();
	Vector<Vector<Color>> data;

	for (unsigned i = 0;i < newHeight;i++)
	{
		unsigned img1Size = img1->getData()[i].getSize();
		Vector<Color> newRow;
		for (unsigned j = 0;j < newWidth;j++)
		{
			BitSet newData(newHeight, Utility::minimumBitsToStore(img1->getColorValue()));
			unsigned newDataR = 0;
			unsigned newDataG = 0;
			unsigned newDataB = 0;
			if (j > img1Size)
			{
				newDataR = img2->getData()[i][j - img1Size - 1].r();
				newDataG = img2->getData()[i][j - img1Size - 1].g();
				newDataB = img2->getData()[i][j - img1Size - 1].b();
			}
			else if (i >= img1->getData().getSize())
			{
				newDataR = img2->getData()[i - img1->getData().getSize()][j].r();
				newDataG = img2->getData()[i - img1->getData().getSize()][j].g();
				newDataB = img2->getData()[i - img1->getData().getSize()][j].b();
			}
			else
			{
				newDataR = img2->getData()[i][j].r();
				newDataG = img2->getData()[i][j].g();
				newDataB = img2->getData()[i][j].b();
			}
			newData.setNumber(Utility::RED_POSITION, newDataR);
			newData.setNumber(Utility::GREEN_POSITION, newDataG);
			newData.setNumber(Utility::BLUE_POSITION, newDataB);
			Color newColor(newData);
			newRow.pushBack(newColor);
		}
		data.pushBack(newRow);
	}

	return new PixMap(magicNumber, newWidth, newHeight, header, saveFileName, img1->getColorValue(), data);
}


