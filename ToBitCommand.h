#pragma once
#include "CommandVector.h"

class ToBitCommand : public CommandVector
{
public:

	ToBitCommand(Vector<Polymorphic_Ptr<NetPbm>>& data);

	void execute() override;
	void undo() override;
	CommandVector* clone()const override;
private:
	NetPbm* GrayMapToBit(unsigned idx);
	NetPbm* PixMapToBit(unsigned idx);
};