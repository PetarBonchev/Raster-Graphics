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
	Vector<MyString> words = separate(message, ' ');
	if (!std::strcmp(words[0].c_str(), "collage"))
	{
		unsigned img1Idx = 0, img2Idx = 0;
		for (unsigned i = 0;i < SessionManager::getInstance().getCurrentSession()->getImages().getSize();i++)
		{
			if (!std::strcmp(SessionManager::getInstance().getCurrentSession()->getImages()[i]->getFilename().c_str(), words[2].c_str()))
				img1Idx = i;
			if (!std::strcmp(SessionManager::getInstance().getCurrentSession()->getImages()[i]->getFilename().c_str(), words[3].c_str()))
				img2Idx = i;
		}
		return new CollageCommand(SessionManager::getInstance().getCurrentSession()->getImages(), img1Idx, img2Idx, !std::strcmp(words[1].c_str(), "horizontal"), words[4]);
	}

	throw std::logic_error("Command not recognized");

	return nullptr;
}

Vector<MyString> CommandFactory::separate(const MyString& line, const char separator)
{
	Vector<MyString> ret;
	char buffer[Utility::BUFFER_SIZE];
	unsigned bufferLen = 0;
	for (unsigned i = 0;i < line.lenght();i++)
	{
		if (line[i] == separator)
		{
			if (bufferLen == 0)
				continue;
			buffer[bufferLen] = Utility::TERMINATE_SYMBOL;
			ret.pushBack(MyString(buffer));
			bufferLen = 0;
			continue;
		}

		buffer[bufferLen++] = line[i];
	}

	if (bufferLen > 0)
	{
		buffer[bufferLen] = Utility::TERMINATE_SYMBOL;
		ret.pushBack(MyString(buffer));
	}

	return ret;
}
