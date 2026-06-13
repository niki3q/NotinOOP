#include "CommandRouter.h"
#include "BuyerCommands.h"
#include "AdminCommands.h"
#include "Load.h"
#include "Save.h"
#include <iostream>
#include <sstream>

CommandRouter::CommandRouter() : currentUser(nullptr) {
    Load::fromFile(DB_FILE, users, fragrances, purchases);

    bool hasAdmin = false;
    for (User* u : users)
        if (u->isAdmin()) { hasAdmin = true; break; }

    if (!hasAdmin) {
        users.push_back(new Admin("admin", "admin1914"));
        std::cout << "[System] Default admin: admin / admin1914\n";
    }

    if (fragrances.empty()) {
        fragrances.emplace_back("Sauvage", Brand::DIOR, 95.0, FragranceFamily::WOODY, 20);
        fragrances.emplace_back("Acqua-di-Gio", Brand::ARMANI, 80.0, FragranceFamily::AQUATIC, 15);
        fragrances.emplace_back("Black-Orchid", Brand::GUCCI, 120.0, FragranceFamily::ORIENTAL, 10);
        fragrances.emplace_back("L'Homme", Brand::YSL, 90.0, FragranceFamily::WOODY, 12);
        fragrances.emplace_back("Baccarat-540", Brand::XERJOFF, 300.0, FragranceFamily::FLORAL, 5);
    }
}

CommandRouter::~CommandRouter() {
    for (User* u : users) delete u;
}

User* CommandRouter::findUser(const std::string& username) {
    for (User* u : users)
        if (u->getUsername() == username) return u;
    return nullptr;
}

Fragrance* CommandRouter::findFragrance(const std::string& name) {
    for (Fragrance& f : fragrances)
        if (f.getName() == name) return &f;
    return nullptr;
}

Purchase* CommandRouter::findPurchase(int id) {
    for (Purchase& p : purchases)
        if (p.getPurchaseId() == id) return &p;
    return nullptr;
}

Buyer* CommandRouter::findBuyer(int userId) {
    for (User* u : users)
        if (u->getUserId() == userId && !u->isAdmin())
            return static_cast<Buyer*>(u);
    return nullptr;
}

void CommandRouter::handleRegister(const std::string& username, const std::string& password)
{
    if (findUser(username)) {
        std::cout << "  Username '" << username << "' is already taken.\n";
        return;
    }
    users.push_back(new Buyer(username, password));
    std::cout << "  Registered! You can now login.\n";
}

void CommandRouter::handleLogin(const std::string& username, const std::string& password)
{
    User* u = findUser(username);
    if (!u || u->getPassword() != password) {
        std::cout << "  Wrong username or password.\n";
        return;
    }
    if (u->isBlocked()) {
        std::cout << "  This account has been blocked.\n";
        return;
    }
    currentUser = u;
    std::cout << "  Welcome, " << username << "! (" << u->getRole() << ")\n";
}

void CommandRouter::handleLogout() {
    std::cout << "  Goodbye, " << currentUser->getUsername() << "!\n";
    currentUser = nullptr;
}

void CommandRouter::handleListFragrances() {
    if (fragrances.empty()) { std::cout << "  No fragrances in catalogue.\n"; return; }
    std::cout << "\n";
    std::cout << "  +----+----------------------+------------+-----------+--------+-------+--------+\n";
    std::cout << "  | #  | Name                 | Brand      | Family    | Price  | Stock | Rating |\n";
    std::cout << "  +----+----------------------+------------+-----------+--------+-------+--------+\n";
    for (Fragrance& f : fragrances) f.show();
    std::cout << "  +----+----------------------+------------+-----------+--------+-------+--------+\n\n";
}

void CommandRouter::run() {
    std::cout << "()>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~<()\n";
    std::cout << "||                                  ||\n";
    std::cout << "||     NotinOOP Fragrance Store     ||\n";
    std::cout << "||                                  ||\n";
    std::cout << "()>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~<()\n";
    std::cout << "Commands: register / login / list-fragrances / end \n";

    BuyerCommands buyerCmd(*this);
    AdminCommands adminCmd(*this);

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        //without login
        if (cmd == "end") {
            Save::toFile(DB_FILE, users, fragrances, purchases);
            std::cout << "  Data saved. Goodbye!\n";
            break;
        }

        if (cmd == "list-fragrances") { handleListFragrances(); continue; }

        if (!currentUser) {
            if (cmd == "register") { std::string u, p; iss >> u >> p; handleRegister(u, p); }
            else if (cmd == "login") { std::string u, p; iss >> u >> p; handleLogin(u, p); }
            else { std::cout << "  Please login first.\n"; }
            continue;
        }

        //avail for all
        if (cmd == "logout") { handleLogout(); continue; }
        if (cmd == "help") { currentUser->showHelp(); continue; }

        //buyer
        if (!currentUser->isAdmin()) {
            if (cmd == "add-to-balance") { double a; iss >> a; buyerCmd.addToBalance(a); }
            else if (cmd == "add-to-cart") {
                std::string name;
                std::getline(iss >> std::ws, name);
                buyerCmd.addToCart(name);
            }
            else if (cmd == "remove-from-cart") {
                std::string name;
                std::getline(iss >> std::ws, name);
                buyerCmd.removeFromCart(name);
            }
            else if (cmd == "view-cart") { buyerCmd.viewCart(); }
            else if (cmd == "add-to-wishlist") {
                std::string name;
                std::getline(iss >> std::ws, name);
                buyerCmd.addToWishlist(name);
            }
            else if (cmd == "remove-from-wishlist") {
                std::string name;
                std::getline(iss >> std::ws, name);
                buyerCmd.removeFromWishlist(name);
            }
            else if (cmd == "recommend") { buyerCmd.recommend(); }
            else if (cmd == "checkout") { buyerCmd.checkout(); }
            else if (cmd == "cancel") { int id; iss >> id; buyerCmd.cancel(id); }
            else if (cmd == "view-bought") { buyerCmd.viewBought(); }
            else if (cmd == "view-purchases") { buyerCmd.viewPurchases(); }
            else if (cmd == "make-review") {
                std::string word, fragName;
                double rating = -1;
                std::string comment;
                while (iss >> word) {
                    try {
                        rating = std::stod(word);
                        std::getline(iss >> std::ws, comment);
                        break;
                    }
                    catch (...) {
                        if (!fragName.empty()) fragName += " ";
                        fragName += word;
                    }
                }
                if (rating < 0) std::cout << "  Usage: make-review <name> <rating> <comment>\n";
                else buyerCmd.makeReview(fragName, rating, comment);
            }
            else { std::cout << "  Unknown command. Type 'help'.\n"; }
            continue;
        }

        //admin
        if (cmd == "create-admin") { std::string u, p; iss >> u >> p; adminCmd.createAdmin(u, p); }
        else if (cmd == "block-user") { std::string u; iss >> u; adminCmd.blockUser(u); }
        else if (cmd == "create-fragrance") {
            std::string name, brand, family; double price;
            iss >> name >> brand >> price >> family;
            adminCmd.createFragrance(name, brand, price, family);
        }
        else if (cmd == "add-quantity") { std::string n; int q; iss >> n >> q; adminCmd.addQuantity(n, q); }
        else if (cmd == "deliver") { int id; iss >> id; adminCmd.deliver(id); }
        else if (cmd == "remove-review") { int fid, rid; iss >> fid >> rid; adminCmd.removeReview(fid, rid); }
        else { std::cout << "  Unknown command. Type 'help'.\n"; }
    }
}