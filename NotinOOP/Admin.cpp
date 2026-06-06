#include "Admin.h"

Admin:: Admin() : User() {}

Admin::Admin(const std::string& username, const std::string& password)
    : User(username, password) 
{}
Admin::Admin(int id, const std::string& username, const std::string& password, bool blocked)
    : User(id, username, password, blocked) 
{}

bool Admin::isAdmin() const  
{ 
    return true; 
}
std::string Admin::getType() const
{ 
    return "ADMIN"; 
}

void Admin::showHelp() const 
{
    std::cout << "  Available commands (Admin):\n"
        << "block-user\n"
        << "create-fragrance \n"
        << "add-quantity \n"
        << "deliver\n"
        << "remove-review\n"
        << "logout\n"
        << "help\n";
}
