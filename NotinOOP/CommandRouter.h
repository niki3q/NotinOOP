#pragma once
#include "Buyer.h"
#include "Admin.h"
#include "Fragrance.h"
#include "Purchase.h"
#include "Load.h"
#include "Save.h"
#include <vector>
#include <string>

class BuyerCommands;
class AdminCommands;

class CommandRouter {
public:
    std::vector<User*>     users;
    std::vector<Fragrance> fragrances;
    std::vector<Purchase>  purchases;
    User* currentUser;
    const std::string DB_FILE = "database.txt";

    User* findUser(const std::string& username);
    Fragrance* findFragrance(const std::string& name);
    Purchase* findPurchase(int id);
    Buyer* findBuyer(int userId);
private:
    void handleRegister(const std::string& username, const std::string& password);
    void handleLogin(const std::string& username, const std::string& password);
    void handleLogout();
    void handleListFragrances();

public:
    CommandRouter();
    ~CommandRouter();

    void run();
};

