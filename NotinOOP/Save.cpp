#include "Save.h"
#include "BonusDiscount.h"
#include "BrandDiscount.h"
#include <fstream>

void Save::toFile(const std::string& filename,
    const std::vector<User*>& users,
    const std::vector<Fragrance>& fragrances,
    const std::vector<Purchase>& purchases)
{
    std::ofstream file(filename);

    file << "USERS\n";
    for (User* u : users) {
        if (u->isAdmin()) {
            file << "ADMIN|" << u->getUserId()
                << "|" << u->getUsername()
                << "|" << u->getPassword()
                << "|" << u->isBlocked() << "\n";
        }
        else {
            Buyer* b = static_cast<Buyer*>(u);
            file << "BUYER|" << b->getUserId()
                << "|" << b->getUsername()
                << "|" << b->getPassword()
                << "|" << b->isBlocked()
                << "|" << b->getBalance()
                << "|" << b->getRemovedReviews() << "|";

            const std::vector<std::string>& wl = b->getWishlist();
            for (size_t i = 0; i < wl.size(); i++) {
                file << wl[i];
                if (i + 1 < wl.size()) file << ",";
            }
            file << "|";

            const std::vector<Discount*>& discs = b->getDiscounts();
            for (size_t i = 0; i < discs.size(); i++) {
                Discount* d = discs[i];

                if (d->getType() == DiscountType::BONUS) {
                    BonusDiscount* bd = static_cast<BonusDiscount*>(d);
                    file << "BONUS:" << bd->getId()
                        << ":" << bd->getPercent()
                        << ":" << bd->getBonus();

                }
                else if (d->getType() == DiscountType::BRAND) {
                    BrandDiscount* bd = static_cast<BrandDiscount*>(d);
                    file << "BRAND:" << bd->getId()
                        << ":" << bd->getPercent()
                        << ":" << brandToString(bd->getBrand());

                }
                else {
                    file << "BASE:" << d->getId()
                        << ":" << d->getPercent();
                }

                if (i + 1 < discs.size()) file << ";";
            }
            file << "\n";
        }
    }

    file << "FRAGRANCES\n";
    for (const Fragrance& fr : fragrances) {
        file << fr.getFragranceId()
            << "|" << fr.getName()
            << "|" << brandToString(fr.getBrand())
            << "|" << familyToString(fr.getFamily())
            << "|" << fr.getPrice()
            << "|" << fr.getQuantity() << "\n";
    }

    file << "REVIEWS\n";
    for (const Fragrance& fr : fragrances) {
        for (const Review& r : fr.getReviews()) {
            file << fr.getName()
                << "|" << r.getReviewId()
                << "|" << r.getUserId()
                << "|" << r.getRating()
                << "|" << r.getComment() << "\n";
        }
    }

    file << "PURCHASES\n";
    for (const Purchase& p : purchases) {
        file << p.getPurchaseId()
            << "|" << p.getUserId()
            << "|" << statusToString(p.getStatus())
            << "|" << p.getTotalPrice() << "|";

        const std::vector<std::string>& names = p.getFragranceNames();
        for (size_t i = 0; i < names.size(); i++) {
            file << names[i];
            if (i + 1 < names.size()) file << ",";
        }
        file << "\n";
    }
}