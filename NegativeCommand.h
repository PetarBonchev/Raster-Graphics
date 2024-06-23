#pragma once
#include "CommandVector.h"

class NegativeCommand : public CommandVector
{
public:
	NegativeCommand(Vector<Polymorphic_Ptr<NetPbm>>& data);

	void execute() override;
	void undo() override;
	CommandVector* clone()const override;
	MyString message()const override;

	~NegativeCommand() = default;
private:
};