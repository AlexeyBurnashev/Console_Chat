#include "Chat.h"
#include "Bad_Login.h"
#include <iostream>

void Chat::start()
{
	chatStart_ = true;
}

void Chat::startMessage()
{
	std::cout << "--------- Welcom to the chat --------" << std::endl;
}

std::shared_ptr<User> Chat::getUserLogin(const std::string& login) const
{
	for (auto& user : users_)
	{
		if (login == user.getLogin())
			return std::make_shared<User>(user);
	}

	return nullptr;
}

std::shared_ptr<User> Chat::getUserName(const std::string& name) const
{
	for (auto& user : users_)
	{
		if (name == user.getName())
			return std::make_shared<User>(user);
	}

	return nullptr;
}

void Chat::login() 
{
	std::string login, password;
	char operation;

	do
	{
		std::cout << "login: ";
		std::cin >> login;
		std::cout << "password: ";
		std::cin >> password;

		currentUser_ = getUserLogin(login);

		if (currentUser_ == nullptr || (password != currentUser_->getPassword()))
		{
			currentUser_ == nullptr;

			std::cout << std::endl << "login failed..." << std::endl;
			std::cout << "enter (3) to return or (any key) repeat: ";
			std::cin >> operation;

			if (operation == '3')
				break;
		}
	} while (!currentUser_);
}

void Chat::signUp() 
{
	std::string login, password, name;

	std::cout << std::endl << "Enter login: ";
	std::cin >> login;
	std::cout << "Enter password: ";
	std::cin >> password;
	std::cout << "Enter name: ";
	std::cin >> name;

	if (getUserLogin(login) || login == "all")
	{
		throw Bad_Login();
	}

	if (getUserName(name) || name == "all")
	{
		throw Bad_Name();
	}

	User user = User(login, password, name);
	users_.push_back(user);
	currentUser_ = std::make_shared<User>(user);
}

void Chat::showChat() 
{
	std::string from;
	std::string to;

	std::cout << std::endl << "--- Ghat ---" << std::endl;

	for (auto& mess : messages_)
	{
		if (currentUser_->getLogin() == mess.getFrom() || currentUser_->getLogin() == mess.getTo() || mess.getTo() == "all")
		{
			from = (currentUser_->getLogin() == mess.getFrom()) ? "me" : getUserLogin(mess.getFrom())->getName();

			if (mess.getTo() == "all")
			{
				to = "(all)";
			}
			else
			{
				to = (currentUser_->getLogin() == mess.getTo()) ? "me" : getUserLogin(mess.getTo())->getName();
			}

			std::cout << "Message from " << from << " to " << to << std::endl;
			std::cout << "Text: " << mess.getText() << std::endl;
		}

	}

	std::cout << "------------" << std::endl;
}

void Chat::mainMenu()
{
	currentUser_ = nullptr;

	std::string operation;
	do
	{
		std::cout << std::endl << "Login - 1  Registration - 2  Quit - 3" << std::endl;
		std::cout << std::endl << ">> ";
		std::cin >> operation;

		if (operation.size() > 1) // защита от задвоенного нажатия
		{
			std::cout << std::endl << "1 or 2 or 3" << std::endl;
			std::cout << std::endl << ">> ";
			std::cin >> operation;
		}

		switch (operation.at(0))
		{
		case '1':
			login();
			break;
		case '2':
			try
			{
				signUp();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		case '3':
			chatStart_ = false;
			break;
		default:
			std::cout << "1 or 2 or 3" << std::endl;
			break;

		}


	} while (!currentUser_ && chatStart_);
}

void Chat::userMenu()
{
	std::string operation;

	std::cout << std::endl << "Hi, " << currentUser_->getName() << std::endl;

	while (currentUser_)
	{
		std::cout << std::endl << "Show chat - 1  Add message - 2  Users - 3  Exit - 4" << std::endl;
		std::cout << std::endl << ">> ";
		std::cin >> operation;

		if (operation.size() > 1) // защита от задвоенного нажатия
		{
			std::cout << "unknown choise.." << std::endl;
			std::cout << std::endl << ">> ";
			std::cin >> operation;
		}

		switch (operation.at(0))
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUserName();
			break;
		case '4':
			currentUser_ = nullptr;
			break;
		default:
			std::cout << "unknown choise.." << std::endl;
			break;

		}

	}
}

void Chat::showAllUserName()
{
	std::cout << "--- Users ---" << std::endl;
	for (auto& user : users_)
	{
		std::cout << user.getName();

		if (currentUser_->getLogin() == user.getLogin())
			std::cout << "(me)";
		std::cout << std::endl;
	}
	std::cout << "______________" << std::endl;
}

void Chat::addMessage()
{
	std::string to, text;

	std::cout << std::endl << "To (name) to (all): ";
	std::cin >> to;
	std::cout << "Text: ";
	std::cin.ignore();
	getline(std::cin, text);

	if (!(to == "all" || getUserName(to)))
	{
		std::cout << "error send message: cann't find " << to << std::endl;
		return;
	}

	if (to == "all")
	{
		messages_.push_back(Message{ currentUser_->getLogin(), "all", text });


	}
	else
		messages_.push_back(Message{ currentUser_->getLogin(), getUserName(to)->getLogin(), text });
}