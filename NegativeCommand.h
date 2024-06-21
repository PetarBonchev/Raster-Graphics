#pragma once
#include "CommandVector.h"

class NegativeCommand : public CommandVector
{
	NegativeCommand(Vector<Polymorphic_Ptr<NetPbm>>& data);

	void execute() override;
	void undo() override;
	CommandVector* clone()const override;
private:
};