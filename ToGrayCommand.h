#pragma once
#include "CommandVector.h"

class ToGrayCommand : public CommandVector
{
public:

	ToGrayCommand(Vector<Polymorphic_Ptr<NetPbm>>& data);

	void execute() override;
	void undo() override;
	CommandVector* clone()const override;
	MyString message()const override;
private:
	
	NetPbm* PixMapToGray(unsigned idx);
};