#include "NetPbmSaver.h"
#include <fstream>

void NetPbmSaver::savePbm(const NetPbm* object)
{
	std::ofstream ofs(object->getFilename().c_str());

	ofs << Utility::MAGIC_NUMBER_SYMBOL << object->getMagicNumber() << std::endl;
	for (unsigned i = 0;i < object->getHeader().getSize();i++)
	{
		if(object->getHeader()[i][0] == Utility::COMMENT_SIGN)
			ofs << object->getHeader()[i].c_str() << std::endl;
	}
	ofs << object->getWidth() << Utility::NUMBER_SEPARATOR << object->getHeight() << std::endl;

	ofs.close();

	switch (object->getMagicNumber())
	{
	case Utility::BITMAP_NORMAL_MAGIC_NUMBER:
		saveP1(((BitMap*)(object))); break;
	case Utility::GRAYMAP_NORMAL_MAGIC_NUMBER:
		saveP2(((GrayMap*)(object))); break;
	case Utility::PIXMAP_NORMAL_MAGIC_NUMBER:
		saveP3(((PixMap*)(object))); break;
	case Utility::BITMAP_BINARY_MAGIC_NUMBER:
		saveP4(((BitMap*)(object))); break;
	case Utility::GRAYMAP_BINARY_MAGIC_NUMBER:
		saveP5(((GrayMap*)(object))); break;
	case Utility::PIXMAP_BINARY_MAGIC_NUMBER:
		saveP6(((PixMap*)(object))); break;
	default:
		throw std::logic_error("error creating NetPbm in header part");
		break;
	}
}

void NetPbmSaver::saveP1(const BitMap* object)
{
	std::ofstream ofs(object->getFilename().c_str(), std::ios::app);

	for (unsigned i = 0;i < object->getData().getSize();i++)
	{
		for (unsigned j = 0;j <= object->getData()[i].getMaxNumber();j++)
		{
			ofs << object->getData()[i].getNumber(j) << Utility::NUMBER_SEPARATOR;
		}
		ofs << std::endl;
	}

	ofs.close();
}

void NetPbmSaver::saveP2(const GrayMap* object)
{
	std::ofstream ofs(object->getFilename().c_str(), std::ios::app);

	ofs << object->getMaxGray() << std::endl;
	for (unsigned i = 0;i < object->getData().getSize();i++)
	{
		for (unsigned j = 0;j <= object->getData()[i].getMaxNumber();j++)
		{
			ofs << object->getData()[i].getNumber(j) << Utility::NUMBER_SEPARATOR;
		}
		ofs << std::endl;
	}

	ofs.close();
}

void NetPbmSaver::saveP3(const PixMap* object)
{
	std::ofstream ofs(object->getFilename().c_str(), std::ios::app);

	ofs << object->getColorValue() << std::endl;
	for (unsigned i = 0;i < object->getData().getSize();i++)
	{
		for (unsigned j = 0;j < object->getData()[i].getSize();j++)
		{
			ofs << object->getData()[i][j].r() << Utility::NUMBER_SEPARATOR;
			ofs << object->getData()[i][j].g() << Utility::NUMBER_SEPARATOR;
			ofs << object->getData()[i][j].b() << Utility::NUMBER_SEPARATOR;
		}
		ofs << std::endl;
	}

	ofs.close();
}

void NetPbmSaver::saveP4(const BitMap* object)
{
	std::ofstream ofs(object->getFilename().c_str(), std::ios::app | std::ios::binary);

	for (unsigned i = 0;i < object->getData().getSize();i++)
	{
		for (unsigned j = 0;j <= object->getData()[i].getMaxNumber();j++)
		{
			uint8_t val = object->getData()[i].getNumber(j);
			ofs.write((const char*)&val, sizeof(uint8_t));
		}
	}

	ofs.close();
}

void NetPbmSaver::saveP5(const GrayMap* object)
{
	std::ofstream oofs(object->getFilename().c_str(), std::ios::app);

	oofs << object->getMaxGray() << std::endl;

	oofs.close();


	std::ofstream ofs(object->getFilename().c_str(), std::ios::app | std::ios::binary);

	for (unsigned i = 0;i < object->getData().getSize();i++)
	{
		for (unsigned j = 0;j <= object->getData()[i].getMaxNumber();j++)
		{
			uint8_t val = object->getData()[i].getNumber(j);
			ofs.write((const char*)&val, sizeof(uint8_t));
		}
	}

	ofs.close();
}

void NetPbmSaver::saveP6(const PixMap* object)
{
	std::ofstream oofs(object->getFilename().c_str(), std::ios::app);

	oofs << object->getColorValue() << std::endl;

	oofs.close();


	std::ofstream ofs(object->getFilename().c_str(), std::ios::app | std::ios::binary);

	for (unsigned i = 0;i < object->getData().getSize();i++)
	{
		for (unsigned j = 0;j < object->getData()[i].getSize();j++)
		{
			uint8_t r = object->getData()[i][j].r();
			uint8_t g = object->getData()[i][j].g();
			uint8_t b = object->getData()[i][j].b();

			ofs.write((const char*)&r, sizeof(uint8_t));
			ofs.write((const char*)&g, sizeof(uint8_t));
			ofs.write((const char*)&b, sizeof(uint8_t));
		}
	}

	ofs.close();
}
