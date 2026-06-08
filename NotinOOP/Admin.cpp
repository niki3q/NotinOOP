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
std::string Admin::getRole() const
{ 
    return "ADMIN"; 
}

void Admin::showHelp() const 
{
    std::cout << "  Available commands (Admin):\n"
        << "  block-user <username>\n"
        << "  create-fragrance <name> <brand> <price> <family>\n"
        << "  add-quantity <fragrance-name> <quantity>\n"
        << "  deliver <purchase-id>\n"
        << "  remove-review <fragrance-name> <review-id>\n"
        << "  logout\n  help\n";
}
