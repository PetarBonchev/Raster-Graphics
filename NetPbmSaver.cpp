#include "NetPbmSaver.h"
#include <fstream>

void NetPbmSaver::savePbm(const NetPbm* object)
{
	std::ofstream ofs(object->getFilename().c_str());

	for (unsigned i = 0;i < object->getHeader().getSize();i++)
	{
		ofs << object->getHeader()[i].c_str() << std::endl;
	}

	ofs.close();

	std::cout<<"Valid? " << ((PixMap*)(object))->isValid() << std::endl;

	for (unsigned i = 0;i < ((PixMap*)(object))->getData().getSize();i++)
	{
		for (unsigned j = 0;j < ((PixMap*)(object))->getData()[i].getSize();j++)
		{
			std::cout << ((PixMap*)(object))->getData()[i][j].r() << " ";
			std::cout << ((PixMap*)(object))->getData()[i][j].g() << " ";
			std::cout << ((PixMap*)(object))->getData()[i][j].b() << " ";
		}
		std::cout << std::endl;
	}

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
}

void NetPbmSaver::saveP2(const GrayMap* object)
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
}

void NetPbmSaver::saveP3(const PixMap* object)
{
	std::ofstream ofs(object->getFilename().c_str(), std::ios::app);

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
}

void NetPbmSaver::saveP4(const BitMap* object)
{
}

void NetPbmSaver::saveP5(const GrayMap* object)
{
}

void NetPbmSaver::saveP6(const PixMap* object)
{
}
