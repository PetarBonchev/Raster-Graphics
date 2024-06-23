#include "NegativeCommand.h"

NegativeCommand::NegativeCommand(Vector<Polymorphic_Ptr<NetPbm>>& data) : CommandVector(data) {}

void NegativeCommand::execute()
{
	for (unsigned i = 0;i < data.getSize();i++)
	{
		data[i]->negative();
	}
}

void NegativeCommand::undo()
{
}

CommandVector* NegativeCommand::clone() const
{
	return new NegativeCommand(*this);
}

MyString NegativeCommand::message() const
{
	return MyString("negative");
}
