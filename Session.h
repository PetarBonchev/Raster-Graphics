#pragma once
#include "Vector.hpp"
#include "PolymorphicPtr.h"
#include "NetPbm.h"
#include "MyString.h"
#include "CommandVector.h"

class Session
{
public:
	void addCommand(CommandVector* command);
	void addNetpbm(NetPbm* object);
	void execute();
	void executeAll();
	void undo();//not using
	MyString history()const;

	Vector<Polymorphic_Ptr<NetPbm>>& getImages();
	Session* clone() const;

private:
	Vector<Polymorphic_Ptr<NetPbm>> images;
	Vector<Polymorphic_Ptr<CommandVector>> commands;

	unsigned currentCommand = 0;
};