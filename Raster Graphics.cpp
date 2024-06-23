#include <iostream>
#include "NetPbmCreator.h"
#include "NetPbmSaver.h"
#include "SessionManager.h"
#include "CommandFactory.h"

Vector<MyString> separate(const MyString& line, char separator)
{
	char buffer[Utility::BUFFER_SIZE];
}

void readCommand(bool& addImageMode)
{
	char buffer[Utility::BUFFER_SIZE];
	std::cin >> buffer;

	if (buffer[0] == 'l' && buffer[1] == 'o' && buffer[2] == 'a' && buffer[3] == 'd')
	{
		SessionManager::getInstance().addSession();
		std::cout << "Session with ID: " << SessionManager::getInstance().getSessionsCount() << " started" << std::endl;

		addImageMode = true;

		MyString str(buffer + 5);
		NetPbm* obj = NetPbmCreator::readPbm(str);
		SessionManager::getInstance().getCurrentSession()->addNetpbm(obj);
		std::cout << "Image \"" << obj->getFilename() << "\" added" << std::endl;
	}
	else if (buffer[0] == 'a' && buffer[1] == 'd' && buffer[2] == 'd')
	{
		addImageMode = true;
	}

}

void programLoop()
{
	try
	{
		bool addMode = false;
		while (true)
		{
			try
			{
				readCommand(addMode);
			}
			catch (std::logic_error err)
			{
				std::cout << "WARNING! " << err.what() << std::endl;
			}

		}

	}
	catch (std::exception ex)
	{
		std::cout << "FATAL ERROR: " << ex.what();
	}
}

int main()
{
	try
	{
		MyString str("test1.pbm");
		SessionManager::getInstance().addSession();
		NetPbm* obj = NetPbmCreator::readPbm(str);
		SessionManager::getInstance().getCurrentSession()->addNetpbm(obj);
		CommandVector* newCommand = CommandFactory::createCommand(MyString("grayscale"));
		SessionManager::getInstance().getCurrentSession()->addCommand(newCommand);
		SessionManager::getInstance().getCurrentSession()->execute();
		NetPbmSaver::savePbm(SessionManager::getInstance().getCurrentSession()->getImages()[0].get());
		/*SessionManager::getInstance().getCurrentSession()->addCommand(CommandFactory::createCommand(MyString("negative")));
		*/
	}
	catch (std::exception ex)
	{
		std::cout << ex.what();
	}
	/*
	Polymorphic_Ptr<NetPbm> obj(NetPbmCreator::readPbm(str));
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