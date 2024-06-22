#include "RotateCommand.h"

RotateCommand::RotateCommand(Vector<Polymorphic_Ptr<NetPbm>>& data, bool rotateLeft) : CommandVector(data), rotateLeft(rotateLeft) {}

void RotateCommand::execute()
{
	for (unsigned i = 0;i < data.getSize();i++)
	{
		data[i]->rotate(rotateLeft);
	}
}
