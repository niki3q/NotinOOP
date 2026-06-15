#include "Load.h"
#include "BonusDiscount.h"
#include "BrandDiscount.h"
#include <fstream>
#include <sstream>

std::vector<std::string> Load::split(const std::string& s, char delim) {
    std::vector<std::string> tokens;
    std::istringstream ss(s);
    std::string tok;
    while (std::getline(ss, tok, delim))
        tokens.push_back(tok);
    return tokens;
}

// USERS
//   ADMIN|id|username|password|blocked
//   BUYER|id|username|password|blocked|balance|removedReviews|wishlist|discounts
//
// FRAGRANCES
//   id|name|brand|family|price|quantity
//
// REVIEWS
//   fragranceName|reviewId|userId|rating|comment
//
// PURCHASES
//   id|userId|status|total|name1,name2,...

void Load::fromFile(const std::string& filename,
    std::vector<User*>& users,
    std::vector<Fragrance>& fragrances,
    std::vector<Purchase>& purchases)
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    std::string section;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line == "USERS" || line == "FRAGRANCES" ||
            line == "REVIEWS" || line == "PURCHASES") {
            section = line;
            continue;
        }

        std::vector<std::string> t = split(line, '|');

        if (section == "USERS" && t.size() >= 5) {
            int  id = std::stoi(t[1]);
            std::string uname = t[2];
            std::string pass = t[3];
            bool blocked = (t[4] == "1");

            if (t[0] == "ADMIN") {
                users.push_back(new Admin(id, uname, pass, blocked));

            }
            else if (t[0] == "BUYER" && t.size() >= 7) {
                double balance = std::stod(t[5]);
                int removedRevs = std::stoi(t[6]);

                Buyer* b = new Buyer(id, uname, pass, blocked, balance, removedRevs);

                if (t.size() > 7 && !t[7].empty()) {
                    for (const std::string& w : split(t[7], ','))
                        b->addToWishlist(w);
                }

                if (t.size() > 8 && !t[8].empty()) {
                    for (const std::string& entry : split(t[8], ';')) {
                        std::vector<std::string> d = split(entry, ':');
                        if (d.size() < 3) continue;
                        int did = std::stoi(d[1]);
                        double pct = std::stod(d[2]);

                        if (d[0] == "BONUS" && d.size() >= 4)
                            b->addDiscount(new BonusDiscount(did, pct, std::stod(d[3])));
                        else if (d[0] == "BRAND" && d.size() >= 4)
                            b->addDiscount(new BrandDiscount(did, pct, brandFromString(d[3])));
                        else
                            b->addDiscount(new Discount(did, pct));
                    }
                }

                users.push_back(b);
            }
            User::setNextId(id);
        }

        else if (section == "FRAGRANCES" && t.size() >= 6) {
            int id = std::stoi(t[0]);
            fragrances.emplace_back(id, t[1], brandFromString(t[2]), std::stod(t[4]),
                familyFromString(t[3]), std::stoi(t[5]));
            Fragrance::setNextId(id);
        }

        else if (section == "REVIEWS" && t.size() >= 5) {
            std::string fragName = t[0];
            int rId = std::stoi(t[1]);
            int uId = std::stoi(t[2]);
            double rat = std::stod(t[3]);
            std::string  comm = t[4];

            for (Fragrance& fr : fragrances) {
                if (fr.getName() == fragName) {
                    fr.addReview(Review(rId, uId, fragName, rat, comm));
                    Review::setNextId(rId);
                    break;
                }
            }
        }

        else if (section == "PURCHASES" && t.size() >= 5) {
            int id = std::stoi(t[0]);
            int uid = std::stoi(t[1]);
            PurchaseStatus st = statusFromString(t[2]);
            double tot = std::stod(t[3]);
            std::vector<std::string> names = split(t[4], ',');

            purchases.emplace_back(id, uid, st, tot, names);
            Purchase::setNextId(id);
        }
    }
}
