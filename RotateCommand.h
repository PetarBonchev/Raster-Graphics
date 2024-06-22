#pragma once
#include "CommandVector.h"

class RotateCommand : public CommandVector
{
public:

	RotateCommand(Vector<Polymorphic_Ptr<NetPbm>>& data, bool rotateLeft);

	virtual void execute() = 0;
	virtual void undo() = 0;

	virtual ~RotateCommand() = default;
	virtual CommandVector* clone()const = 0;

private:
	bool rotateLeft = false;
};