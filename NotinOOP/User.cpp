#include "User.h"

int User::nextId = 1;

User::User() 
    : userId(0), blocked(false)
{}

User::User(const std::string& username, const std::string& password)
    : userId(nextId++), username(username), password(password), blocked(false) 
{}

User::User(int id, const std::string& username, const std::string& password, bool blocked)
    : userId(id), username(username), password(password), blocked(blocked) 
{
    if (id >= nextId) nextId = id + 1;
}

int User::getUserId() const 
{
    return userId;
}
const std::string& User::getUsername() const 
{
    return username; 
}
const std::string& User::getPassword() const
{ 
    return password;
}
bool User::isBlocked() const 
{ 
    return blocked;
}
void User::setBlocked(bool b) 
{ 
    blocked = b; 
}

bool User::isAdmin() const 
{ 
    return false;
}

std::string User::getRole() const 
{ 
    return "USER";
}

void User::setNextId(int id) 
{ 
    nextId = id; 
}

int User::getNextId() 
{ 
    return nextId; 
}
