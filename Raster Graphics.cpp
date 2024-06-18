#include <iostream>
#include "MyString.h"
#include "BitSet.h"
#include "Vector.hpp"
#include "NetPbmCreator.h"

int main()
{
	NetPbm* WORK = NetPbmCreator::readPbm(MyString("test1.pbm"));
	std::cout << WORK->magicNumber << std::endl;
	std::cout << WORK->width << std::endl;
	std::cout << WORK->height << std::endl;
	for (unsigned i = 0; i < WORK->header.getSize(); i++)
	{
		std::cout << WORK->header[i] << std::endl;
	}
	std::cout << "gray: " << ((GrayMap*)WORK)->maxGray << std::endl;
	for (unsigned i = 0; i < ((GrayMap*)WORK)->data.getSize(); i++)
	{
		for (unsigned j = 0; j < ((GrayMap*)WORK)->data[i].getMaxNumber(); j++)
		{
			std::cout << ((GrayMap*)WORK)->data[i].getNumber(j) << " ";
		}
		std::cout << std::endl;
	}

	MyString str("12 3 444 0");

	Vector<unsigned> v;
	v = strToVector(str);

	for (unsigned i = 0; i < v.getSize(); i++)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}