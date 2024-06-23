#pragma once

#include "NegativeCommand.h"
#include "RotateCommand.h"
#include "ToBitCommand.h"
#include "ToGrayCommand.h"
#include "SessionManager.h"
#include "CollageCommand.h"

class CommandFactory
{
public:
	static CommandVector* createCommand(const MyString& message);
	static Vector<MyString> separate(const MyString& str, const char separator);
};