#pragma once
#include "User.h"
#include <iostream>

class Admin : public User
{
public:
	Admin();
	Admin(const std::string& username, const std::string& password);
	Admin(int id, const std::string& username, const std::string& password, bool blocked);

	bool isAdmin() const override;
	std::string getRole() const override;
	void showHelp() const override;
};

