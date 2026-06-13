#include "Admin.h"

Admin::Admin() : User() {}

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
    std::cout << "\n"
        << "  *-------------------------------------------------------------*\n"
        << "  |                     Admin Commands                          |\n"
        << "  |-------------------------------------------------------------|\n"
        << "  | create-admin u p         | create a new admin account       |\n"
        << "  | block-user <username>    | block & delete a user            |\n"
        << "  | create-fragrance n b p f | new fragrance (name brand $ fam) |\n"
        << "  | add-quantity <name> <n>  | add stock to a fragrance         |\n"
        << "  | deliver <purchase-id>    | mark purchase as delivered       |\n"
        << "  | remove-review <fid> <rid>| remove a review by ids           |\n"
        << "  | list-fragrances          | show full catalogue              |\n"
        << "  | logout                   | log out                          |\n"
        << "  | help                     | show this menu                   |\n"
        << "  *-------------------------------------------------------------*\n\n";
}