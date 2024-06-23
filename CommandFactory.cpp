#include "CommandFactory.h"

CommandVector* CommandFactory::createCommand(const MyString& message)
{
	if (!std::strcmp(message.c_str(), "grayscale"))
	{
		return new ToGrayCommand(SessionManager::getInstance().getCurrentSession()->getImages());
	}
	if (!std::strcmp(message.c_str(), "monochrome"))
	{
		return new ToBitCommand(SessionManager::getInstance().getCurrentSession()->getImages());
	}
	if (!std::strcmp(message.c_str(), "negative"))
	{
		return new NegativeCommand(SessionManager::getInstance().getCurrentSession()->getImages());
	}
	if (!std::strcmp(message.c_str(), "rotate left"))
	{
		return new RotateCommand(SessionManager::getInstance().getCurrentSession()->getImages(), true);
	}
	if (!std::strcmp(message.c_str(), "rotate right"))
	{
		return new RotateCommand(SessionManager::getInstance().getCurrentSession()->getImages(), false);
	}

	throw std::logic_error("Command not recognized");

	return nullptr;
}
