#include "Database.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::string> Database::split(const std::string& s, char delim) {
    std::vector<std::string> tokens;
    std::istringstream ss(s);
    std::string tok;
    while (std::getline(ss, tok, delim)) tokens.push_back(tok);
    return tokens;
}


void Database::load(const std::string& filename,
    std::vector<User*>& users,
    std::vector<Fragrance>& fragrances,
    std::vector<Purchase>& purchases)
{
    std::ifstream f(filename);
    if (!f.is_open()) return; 

    std::string line;
    std::string section;

    while (std::getline(f, line)) {
        if (line.empty()) continue;

        if (line == "USERS" || line == "FRAGRANCES" ||
            line == "REVIEWS" || line == "PURCHASES") {
            section = line;
            continue;
        }

        if (section == "USERS") {
            auto t = split(line, '|');
            if (t.size() < 5) continue;

            std::string role = t[0];
            int  id = std::stoi(t[1]);
            std::string uname = t[2];
            std::string pass = t[3];
            bool blocked = (t[4] == "1");

            if (role == "ADMIN") {
                users.push_back(new Admin(id, uname, pass, blocked));
            }
            else if (role == "BUYER" && t.size() >= 7) {
                double bal = std::stod(t[5]);
                int    remR = std::stoi(t[6]);
                auto* b = new Buyer(id, uname, pass, blocked, bal, remR);

                if (t.size() > 7 && !t[7].empty()) {
                    auto wl = split(t[7], ',');
                    for (auto& w : wl) b->addToWishlist(w);
                }
                if (t.size() > 8 && !t[8].empty()) {
                    auto dents = split(t[8], ';');
                    for (auto& de : dents) {
                        auto dt = split(de, ':');
                        if (dt.size() < 3) continue;
                        std::string dtype = dt[0];
                        int did = std::stoi(dt[1]);
                        double dp = std::stod(dt[2]);
                        if (dtype == "BONUS" && dt.size() >= 4) {
                            b->addDiscount(new BonusDiscount(did, dp, std::stod(dt[3])));
                        }
                        else if (dtype == "BRAND" && dt.size() >= 4) {
                            b->addDiscount(new BrandDiscount(did, dp, brandFromString(dt[3])));
                        }
                        else {
                            b->addDiscount(new Discount(did, dp));
                        }
                    }
                }
                users.push_back(b);
            }
            User::setNextId(id);
        }

        else if (section == "FRAGRANCES") {
            auto t = split(line, '|');
            if (t.size() < 6) continue;
            int id = std::stoi(t[0]);
            fragrances.emplace_back(id, t[1],
                brandFromString(t[2]), std::stod(t[4]),
                familyFromString(t[3]), std::stoi(t[5]));
            Fragrance::setNextId(id);
        }

        else if (section == "REVIEWS") {
            auto t = split(line, '|');
            if (t.size() < 5) continue;
            std::string fragName = t[0];
            int  rId = std::stoi(t[1]);
            int  uId = std::stoi(t[2]);
            double rat = std::stod(t[3]);
            std::string comm = t[4];
            for (auto& fr : fragrances) {
                if (fr.getName() == fragName) {
                    fr.addReview(Review(rId, uId, fragName, rat, comm));
                    Review::setNextId(rId);
                    break;
                }
            }
        }

        else if (section == "PURCHASES") {
            auto t = split(line, '|');
            if (t.size() < 5) continue;
            int id = std::stoi(t[0]);
            int uid = std::stoi(t[1]);
            PurchaseStatus st = statusFromString(t[2]);
            double tot = std::stod(t[3]);
            auto names = split(t[4], ',');
            Purchase p(id, uid, st, tot, names);
            purchases.push_back(p);
            Purchase::setNextId(id);
        }
    }
}

void Database::save(const std::string& filename,
    const std::vector<User*>& users,
    const std::vector<Fragrance>& fragrances,
    const std::vector<Purchase>& purchases)
{
    std::ofstream f(filename);

    f << "USERS\n";
    for (auto* u : users) {
        if (u->isAdmin()) {
            f << "ADMIN|" << u->getUserId() << "|" << u->getUsername()
                << "|" << u->getPassword() << "|" << u->isBlocked() << "\n";
        }
        else {
            auto* b = static_cast<Buyer*>(u);
            f << "BUYER|" << b->getUserId() << "|" << b->getUsername()
                << "|" << b->getPassword() << "|" << b->isBlocked()
                << "|" << b->getBalance() << "|" << b->getRemovedReviews() << "|";

            // wishlist
            const auto& wl = b->getWishlist();
            for (size_t i = 0; i < wl.size(); ++i) {
                f << wl[i];
                if (i + 1 < wl.size()) f << ",";
            }
            f << "|";

            // discounts
            const auto& discs = b->getDiscounts();
            for (size_t i = 0; i < discs.size(); ++i) {
                auto* d = discs[i];
                if (d->getType() == DiscountType::BONUS) {
                    auto* bd = static_cast<BonusDiscount*>(d);
                    f << "BONUS:" << bd->getId() << ":" << bd->getPercent()
                        << ":" << bd->getBonus();
                }
                else if (d->getType() == DiscountType::BRAND) {
                    auto* bd = static_cast<BrandDiscount*>(d);
                    f << "BRAND:" << bd->getId() << ":" << bd->getPercent()
                        << ":" << brandToString(bd->getBrand());
                }
                else {
                    f << "BASE:" << d->getId() << ":" << d->getPercent();
                }
                if (i + 1 < discs.size()) f << ";";
            }
            f << "\n";
        }
    }

    //fragrances 
    f << "FRAGRANCES\n";
    for (const auto& fr : fragrances) {
        f << fr.getFragranceId() << "|" << fr.getName() << "|"
            << brandToString(fr.getBrand()) << "|"
            << familyToString(fr.getFamily()) << "|"
            << fr.getPrice() << "|" << fr.getQuantity() << "\n";
    }

    //reviews
    f << "REVIEWS\n";
    for (const auto& fr : fragrances) {
        for (const auto& r : fr.getReviews()) {
            f << fr.getName() << "|" << r.getReviewId() << "|"
                << r.getUserId() << "|" << r.getRating() << "|"
                << r.getComment() << "\n";
        }
    }

    //purchases 
    f << "PURCHASES\n";
    for (const auto& p : purchases) {
        f << p.getPurchaseId() << "|" << p.getUserId() << "|"
            << statusToString(p.getStatus()) << "|" << p.getTotalPrice() << "|";
        const auto& names = p.getFragranceNames();
        for (size_t i = 0; i < names.size(); ++i) {
            f << names[i];
            if (i + 1 < names.size()) f << ",";
        }
        f << "\n";
    }
}
