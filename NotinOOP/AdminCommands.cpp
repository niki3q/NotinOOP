#include "AdminCommands.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>

AdminCommands::AdminCommands(CommandRouter& sys) : sys(sys) {}


void AdminCommands::createAdmin(const std::string& username, const std::string& password) {
    if (sys.findUser(username)) {
        std::cout << "  Username '" << username << "' is already taken.\n";
        return;
    }
    sys.users.push_back(new Admin(username, password));
    std::cout << "  Admin '" << username << "' created.\n";
}

void AdminCommands::blockUser(const std::string& username) {
    std::vector<User*>& users = sys.users;

    for (size_t i = 0; i < users.size(); i++) {
        if (users[i]->getUsername() == username) {
            if (users[i]->isAdmin()) {
                std::cout << "  Cannot block an admin.\n";
                return;
            }
            delete users[i];
            users.erase(users.begin() + i);
            std::cout << "  User '" << username << "' blocked and deleted.\n";
            return;
        }
    }
    std::cout << "  User not found.\n";
}

void AdminCommands::createFragrance(const std::string& name, const std::string& brand,
    double price, const std::string& family)
{
    if (sys.findFragrance(name)) {
        std::cout << "  A fragrance with that name already exists.\n";
        return;
    }
    sys.fragrances.emplace_back(name, brandFromString(brand),
        price, familyFromString(family), 0);
    std::cout << "  Fragrance '" << name << "' created.\n";
}

void AdminCommands::addQuantity(const std::string& name, int qty) {
    Fragrance* f = sys.findFragrance(name);
    if (!f) { std::cout << "  Fragrance not found.\n"; return; }
    if (qty < 0) { std::cout << "  Quantity cannot be negative.\n"; return; }
    f->addQuantity(qty);
    std::cout << "  Stock for '" << name << "' is now " << f->getQuantity() << "\n";
}

void AdminCommands::deliver(int purchaseId) {
    Purchase* p = sys.findPurchase(purchaseId);
    if (!p) { std::cout << "  Purchase not found.\n"; return; }

    if (p->getStatus() != PurchaseStatus::PENDING) {
        std::cout << "  Only PENDING purchases can be delivered.\n";
        return;
    }

    p->setStatus(PurchaseStatus::DELIVERED);

    Buyer* b = sys.findBuyer(p->getUserId());
    if (b) {
        for (Purchase& bp : b->getPurchases()) {
            if (bp.getPurchaseId() == purchaseId) {
                bp.setStatus(PurchaseStatus::DELIVERED);
                break;
            }
        }
    }
    else {
        std::cout << "  Warning: buyer no longer exists (was blocked).\n";
    }
    std::cout << "  Purchase #" << purchaseId << " delivered.\n";
}

void AdminCommands::removeReview(int fragranceId, int reviewId) {
    Fragrance* f = nullptr;
    for (Fragrance& fr : sys.fragrances) {
        if (fr.getFragranceId() == fragranceId) { f = &fr; break; }
    }
    if (!f) { std::cout << "  Fragrance not found.\n"; return; }

    int ownerId = -1;
    try {
        const Review * r = f->findReview(reviewId);
        ownerId = r->getUserId();
        f->removeReview(reviewId);
        
    }
     catch (const std::exception& e) {
        std::cout << "  " << e.what() << "\n";
        return;
        
    }
    std::cout << "  Review #" << reviewId << " removed.\n";

    Buyer* owner = sys.findBuyer(ownerId);
    if (owner) {
        owner->incrementRemovedReviews();
        if (owner->isBlocked())
            std::cout << "  User '" << owner->getUsername()
            << "' auto-blocked (7+ reviews removed).\n";
    }
}

void AdminCommands::showUndeliveredPurchases() {
    bool any = false;
    std::cout << "\n";
    std::cout << "  +----------+---------+------------+-----------+------------------------------+\n";
    std::cout << "  | Purchase | Buyer # |   Status   |   Total   | Items                        |\n";
    std::cout << "  +----------+---------+------------+-----------+------------------------------+\n";
    for (const Purchase& p : sys.purchases) {
        if (p.getStatus() == PurchaseStatus::PENDING ||
            p.getStatus() == PurchaseStatus::CANCELED) {

            std::string statusStr;
            if (p.getStatus() == PurchaseStatus::PENDING) { statusStr = "[PENDING]  "; }
            else { statusStr = "[CANCELED] "; }

            std::string itemsList;
            for (size_t i = 0; i < p.getFragranceNames().size(); ++i) {
                if (i > 0) itemsList += ", ";
                itemsList += p.getFragranceNames()[i];
            }
            if (itemsList.size() > 28) {
                itemsList = itemsList.substr(0, 25) + "...";
            }

            std::cout << "  | #" << std::left << std::setw(7) << p.getPurchaseId()
                << " | " << std::left << std::setw(7) << p.getUserId()
                << " | " << statusStr
                << " | $" << std::right << std::setw(8) << std::fixed
                << std::setprecision(2) << p.getTotalPrice()
                << " | " << std::left << std::setw(28) << itemsList << " |\n";
            any = true;
        }
    }
    std::cout << "  +----------+---------+------------+-----------+------------------------------+\n";
    if (!any) std::cout << "  No undelivered purchases.\n";
    std::cout << "\n";
}

void AdminCommands::viewAllReviews() {
    bool any = false;
    std::cout << "\n";
    std::cout << "  +--------+----+--------+-------+----------------------------------------+\n";
    std::cout << "  | Fragrance          | Rev# | User# | Stars | Comment                                |\n";
    std::cout << "  +--------------------+------+-------+-------+----------------------------------------+\n";
    for (const Fragrance& fr : sys.fragrances) {
        for (const Review& r : fr.getReviews()) {
            std::string comment = r.getComment();
            if (comment.size() > 38) comment = comment.substr(0, 35) + "...";
            std::cout << "  | " << std::left << std::setw(18) << fr.getName()
                << " | " << std::left << std::setw(4) << r.getReviewId()
                << " | " << std::left << std::setw(5) << r.getUserId()
                << " | " << std::fixed << std::setprecision(1)
                << std::setw(5) << r.getRating()
                << " | " << std::left << std::setw(38) << comment << " |\n";
            any = true;
        }
    }
    std::cout << "  +--------------------+------+-------+-------+----------------------------------------+\n";
    if (!any) std::cout << "  No reviews found.\n";
    std::cout << "\n";
}

