#pragma once
#include "Vector.hpp"
#include "PolymorphicPtr.h"
#include "NetPbm.h"
#include "MyString.h"

class Session
{
public:
	//add command
	void execute();
	void executeAll();
	void undo();//not using
	MyString history()const;

private:
	Vector<Polymorphic_Ptr<NetPbm>> images;
	//vector command
};