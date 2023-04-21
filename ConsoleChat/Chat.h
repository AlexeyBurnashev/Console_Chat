#pragma once
#include <vector>
#include <memory>
#include "Message.h"

class Chat
{
	bool chatStart_ = false;
	std::vector<User> users_;
	std::vector<Message> messages_;
	std::shared_ptr<User> currentUser_ = nullptr;

	void login();
	void signUp();
	void showChat();
	void showAllUserName();
	void addMessage();
	std::vector<User>& getAllUsers() { return users_; }
	std::vector<Message>& getAllMessages() { return messages_; }
	std::shared_ptr<User> getUserLogin(const std::string& login) const;
	std::shared_ptr<User> getUserName(const std::string& name) const;

public:
	void start();
	void startMessage();
	bool chatStart() const { return chatStart_; }
	std::shared_ptr<User> getCurrentUser() const { return currentUser_; }
	void mainMenu();
	void userMenu();
};
