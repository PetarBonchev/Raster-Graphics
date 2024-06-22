#include <iostream>
#include "MyString.h"
#include "BitSet.h"
#include "Vector.hpp"
#include "NetPbmCreator.h"
#include "NetPbmSaver.h"

int main()
{
	MyString str("test1.pbm");
	try
	{
		NetPbm* obj = NetPbmCreator::readPbm(str);
		obj->rotate(true);
		NetPbmSaver::savePbm(obj);
	}
	catch(std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}
}