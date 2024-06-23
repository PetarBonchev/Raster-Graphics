#pragma once

#include "NegativeCommand.h"
#include "RotateCommand.h"
#include "ToBitCommand.h"
#include "ToGrayCommand.h"
#include "SessionManager.h"

class CommandFactory
{
public:
	static CommandVector* createCommand(const MyString& message);
};