#include <iostream>
#include "NetPbmCreator.h"
#include "NetPbmSaver.h"
#include "SessionManager.h"
#include "CommandFactory.h"

Vector<MyString> separate(const MyString& line, char separator)
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

void readCommand(bool& shouldExit)
{
	std::cout << "> ";

	char buffer[Utility::BUFFER_SIZE];
	std::cin.getline(buffer, Utility::BUFFER_SIZE);
	MyString line(buffer);

	Vector<MyString> words = separate(line, ' ');

	if (words.getSize() == 0)
		throw std::logic_error("Invalid command");

	if (!std::strcmp(words[0].c_str(), "load"))
	{
		if (words.getSize() == 1)
			throw std::logic_error("invalid command");

		SessionManager::getInstance().addSession();
		std::cout << "Session with ID: " << SessionManager::getInstance().getSessionsCount() << " started" << std::endl;

		for (unsigned i = 1;i < words.getSize();i++)
		{
			NetPbm* obj = NetPbmCreator::readPbm(words[i]);
			std::cout << "Image \"" << obj->getFilename().c_str() << "\" added" << std::endl;
			SessionManager::getInstance().getCurrentSession()->addNetpbm(obj);
		}
	}
	else if (!std::strcmp(words[0].c_str(), "add"))
	{
		if (words.getSize() != 2)
			throw std::logic_error("invalid command");

		NetPbm* obj = NetPbmCreator::readPbm(words[1]);
		std::cout << "Image \"" << obj->getFilename() << "\" added" << std::endl;
		SessionManager::getInstance().getCurrentSession()->addNetpbm(obj);
	}
	else if (!std::strcmp(words[0].c_str(), "grayscale") || 
			 !std::strcmp(words[0].c_str(), "monochrome") || 
			 !std::strcmp(words[0].c_str(), "negative"))
	{
		if (words.getSize() != 1)
			throw std::logic_error("invalid command");

		CommandVector* newCommand = CommandFactory::createCommand(words[0]);
		SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
	}
	else if (!std::strcmp(words[0].c_str(), "rotate"))
	{
		if (words.getSize() != 2)
			throw std::logic_error("invalid command");

		CommandVector* newCommand;
		if (!std::strcmp(words[1].c_str(), "left"))
		{
			newCommand = CommandFactory::createCommand("rotate left");
		}
		else if (!std::strcmp(words[1].c_str(), "right"))
		{
			newCommand = CommandFactory::createCommand("rotate right");
		}
		else 
			throw std::logic_error("invalid command");

		SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
	}
	else if (!std::strcmp(words[0].c_str(), "session"))
	{
		if (words.getSize() == 1)
			throw std::logic_error("invalid command");

		if (!std::strcmp(words[1].c_str(), "info"))
		{
			std::cout << SessionManager::getInstance().getCurrentSession()->history() << std::endl;
		}
		else
			throw std::logic_error("invalid command");
	}
	else if (!std::strcmp(words[0].c_str(), "switch"))
	{
		if (words.getSize() != 2)
			throw std::logic_error("invalid command");

		unsigned id = Utility::strToUnsigned(words[1].c_str());
		SessionManager::getInstance().goToSession(id);

		std::cout << "You switched to session with ID: " << id << "!" << std::endl;
	}
	else if (!std::strcmp(words[0].c_str(), "save"))
	{
		if (words.getSize() != 1)
			throw std::logic_error("invalid command");

		SessionManager::getInstance().getCurrentSession()->executeAll();
		SessionManager::getInstance().getCurrentSession()->saveAll();
		std::cout << "Images saved successfully" << std::endl;
	}
	else if (!std::strcmp(words[0].c_str(), "saveas"))
	{
		if (words.getSize() != 2)
			throw std::logic_error("invalid command");

		SessionManager::getInstance().getCurrentSession()->saveFirst(words[1]);
	}
	else if (!std::strcmp(words[0].c_str(), "close"))
	{
		if (words.getSize() != 1)
			throw std::logic_error("invalid command");

		SessionManager::getInstance().getCurrentSession()->executeAll();
		SessionManager::getInstance().getCurrentSession()->saveAll();
		std::cout << "Images saved successfully" << std::endl;
		shouldExit = true;
	}
	else if (!std::strcmp(words[0].c_str(), "exit"))
	{
		if (words.getSize() != 1)
			throw std::logic_error("invalid command");

		shouldExit = true;
	}
	else if (!std::strcmp(words[0].c_str(), "collage"))
	{
		CommandVector* newCommand = CommandFactory::createCommand(line);
		SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
	}
	else if (!std::strcmp(words[0].c_str(), "undo"))
	{
		if (words.getSize() != 1)
			throw std::logic_error("invalid command");

		SessionManager::getInstance().getCurrentSession()->undo();
	}
	else if (!std::strcmp(words[0].c_str(), "help"))
	{
		std::cout << "\nCommand list:\n";
		std::cout << "1. grayscale\n";
		std::cout << "2. monochrome\n";
		std::cout << "3. negative\n";
		std::cout << "4. rotate left\n";
		std::cout << "5. rotate right\n";
		std::cout << "6. collage <horizontal/vertical> <filename1> <filename2> <save filename>\n";
		std::cout << "7. undo - removes last command of type 1-6 from current session\n";
		std::cout << "8. add <filename>\n";
		std::cout << "9. session info\n";
		std::cout << "10. switch <session ID>\n";
		std::cout << "11. load <filename1> <filename2> ... - loads arbitrary number of images\n";
		std::cout << "12. save - executes commands and saves every image to its file\n";
		std::cout << "13. saveas <filename> - saves first image to new file\n";
		std::cout << "14. close - saves and closes\n";
		std::cout << "15. exit - exits without saving\n";
		std::cout << "Press ENTER to complete a command\n";
	}
	else
	{
		throw std::logic_error("invalid command");
	}
	std::cout << std::endl;
}

void programLoop()
{
	try
	{
		bool stop = false;
		while (!stop)
		{
			try
			{
				readCommand(stop);
			}
			catch (std::logic_error err)
			{
				std::cout << "WARNING! " << err.what() << std::endl << std::endl;
			}

		}

	}
	catch (std::exception ex)
	{
		std::cout << "FATAL ERROR: " << ex.what();
	}
	catch (...)
	{
		std::cout << "Undefined fatal error!" << std::endl;
	}
}

int main()
{
	std::cout << "RASTER GRAPHICS\n\n";
	programLoop();

	//try
	//{
	//	MyString str("test1.pbm");
	//	SessionManager::getInstance().addSession();
	//	NetPbm* obj = NetPbmCreator::readPbm(str);
	//	SessionManager::getInstance().getCurrentSession()->addNetpbm(obj);
	//	CommandVector* newCommand = CommandFactory::createCommand(MyString("grayscale"));
	//	SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
	//	SessionManager::getInstance().getCurrentSession()->execute();
	//	NetPbmSaver::savePbm(SessionManager::getInstance().getCurrentSession()->getImages()[0].get());
	//	/*SessionManager::getInstance().getCurrentSession()->addCommand(CommandFactory::createCommand(MyString("negative")));
	//	*/
	//}
	//catch (std::exception ex)
	//{
	//	std::cout << ex.what();
	//}
	///*
	/*Polymorphic_Ptr<NetPbm> obj(NetPbmCreator::readPbm(str));
	Vector<Polymorphic_Ptr<NetPbm>> v;
	v.pushBack(std::move(obj));

	std::cout << v[0]->getFilename() << std::endl;
	
	try
	{
		NetPbm* obj = NetPbmCreator::readPbm(str);
		obj->rotate(true);
		NetPbmSaver::savePbm(obj);
	}
	catch(std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}*/
}