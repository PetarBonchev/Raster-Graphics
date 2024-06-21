#include "NegativeCommand.h"

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