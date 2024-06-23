#include "RotateCommand.h"

RotateCommand::RotateCommand(Vector<Polymorphic_Ptr<NetPbm>>& data, bool rotateLeft) : CommandVector(data), rotateLeft(rotateLeft) {}

void RotateCommand::execute()
{
	for (unsigned i = 0;i < data.getSize();i++)
	{
		data[i]->rotate(rotateLeft);
	}
}

void RotateCommand::undo()
{
}

CommandVector* RotateCommand::clone() const
{
	return new RotateCommand(*this);
}

MyString RotateCommand::message() const
{
	MyString msg("rotate ");
	if (rotateLeft)
		msg += MyString("left");
	else
		msg += MyString("right");
	return msg;
}
