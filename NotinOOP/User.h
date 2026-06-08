#pragma once
#include <string>
#include <vector>
#include "Fragrance.h"
#include "Purchase.h"
#include "Discount.h"

class User
{
protected:
	static int nextId;
	int userId;
	std::string username;
	std::string password;
	bool blocked;

public:
	User();
	User(const std::string& username, const std::string& password);
	User(int id, const std::string& username, const std::string& password, bool blocked);

	virtual ~User() = default;

	int getUserId() const;
	const std::string& getUsername() const;
	const std::string& getPassword() const;
	bool isBlocked() const;
	void setBlocked(bool block);

	virtual bool isAdmin() const;
	virtual std::string getRole() const;

	virtual void showHelp() const = 0;

	static void setNextId(int id);
	static int  getNextId();

};

