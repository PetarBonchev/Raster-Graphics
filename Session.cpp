#include "Session.h"

void Session::addCommand(CommandVector* command)
{
	Polymorphic_Ptr<CommandVector> newCommand(command);
	commands.pushBack(newCommand);
}

void Session::addNetpbm(NetPbm* object)
{
	Polymorphic_Ptr<NetPbm> newPbm(object);
	images.pushBack(newPbm);
}

void Session::execute()
{
	if (currentCommand>=commands.getSize())
		throw std::logic_error("trying to execute missing command");

	commands[currentCommand]->execute();
	currentCommand++;
}

void Session::executeAll()
{
	for (unsigned i = currentCommand;i < commands.getSize();i++)
	{
		commands[i]->execute();
	}

	currentCommand = commands.getSize();
}

void Session::undo()
{
}

MyString Session::history() const
{
	MyString info("Name of images in the session: ");
	for (unsigned i = 0;i < images.getSize();i++)
	{
		info += images[i]->getFilename() + MyString(" ");
	}
	info += MyString("\nPending transformations: ");
	for (unsigned i = currentCommand;i < commands.getSize();i++)
	{
		info += commands[i]->message() + MyString(" ");
	}
	return info;
}

Vector<Polymorphic_Ptr<NetPbm>>& Session::getImages()
{
	return images;
}

Session* Session::clone() const
{
	return new Session(*this);
}
