#pragma once
#include "CommandVector.h"

class RotateCommand : public CommandVector
{
public:

	RotateCommand(Vector<Polymorphic_Ptr<NetPbm>>& data, bool rotateLeft);

	void execute() override;
	void undo() override;

	virtual ~RotateCommand() = default;
	CommandVector* clone()const override;
	MyString message()const override;

private:
	bool rotateLeft = false;
};