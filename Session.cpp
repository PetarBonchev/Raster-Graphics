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
	if (commands.getSize() == 0)
		return;

	commands.popBack();
}

void Session::saveAll() const
{
	for (unsigned i = 0;i < images.getSize();i++)
	{
		NetPbmSaver::savePbm(images[i].get());
	}
}

void Session::saveFirst(const MyString& filename)
{
	if (images.getSize() == 0)
		throw std::logic_error("No image to save in this session");

	images[0]->setFilename(filename);
	NetPbmSaver::savePbm(images[0].get());
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
		info += commands[i]->message();
		if (i < commands.getSize() - 1) 
			info += MyString(", ");
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
