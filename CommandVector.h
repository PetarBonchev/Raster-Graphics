#pragma once
#include "Vector.hpp"
#include "PolymorphicPtr.h"
#include "NetPbm.h"
#include "BitMap.h"
#include "GrayMap.h"
#include "PixMap.h"

class CommandVector
{
public:

	CommandVector(Vector<Polymorphic_Ptr<NetPbm>>& data);

	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual MyString message()const = 0;

	virtual ~CommandVector() = default;
	virtual CommandVector* clone()const = 0;

protected:
	Vector<Polymorphic_Ptr<NetPbm>> &data;
};