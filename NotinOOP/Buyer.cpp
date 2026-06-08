#include "Buyer.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Buyer::Buyer(const std::string& username, const std::string& password)
    : User(username, password), balance(0), removedReviews(0) {
}

Buyer::Buyer(int id, const std::string& username, const std::string& password,
    bool blocked, double balance, int removedReviews)
    : User(id, username, password, blocked),
    balance(balance), removedReviews(removedReviews) {
}

Buyer::~Buyer() {
    for (auto* d : discounts) delete d;
}

void Buyer::showHelp() const {
    std::cout << "  Buyer commands:\n"
        << " add-to-balance \n"
        << " add-to-cart\n"
        << " remove-from-cart \n"
        << " view-cart\n"
        << " add-to-wishlist \n"
        << " remove-from-wishlist \n"
        << " recommend\n"
        << " checkout\n"
        << " cancel\n"
        << " view-bought\n"
        << " view-purchases\n"
        << " make-review \n"
        << " view-discounts\n"
        << " list-fragrances\n"
        << " logout\n"
        << " help\n";
}

void Buyer::addToBalance(double amount) { balance += amount; }

bool Buyer::deductBalance(double amount) {
    if (balance < amount) return false;
    balance -= amount;
    return true;
}

bool Buyer::addToWishlist(const std::string& name) {
    if (isInWishlist(name)) return false;
    wishlist.push_back(name);
    return true;
}

bool Buyer::removeFromWishlist(const std::string& name) {
    for (size_t i = 0; i < wishlist.size(); ++i) {
        if (wishlist[i] == name) {
            wishlist.erase(wishlist.begin() + i);
            return true;
        }
    }
    return false;
}

bool Buyer::isInWishlist(const std::string& name) const {
    for (const auto& n : wishlist)
        if (n == name) return true;
    return false;
}

bool Buyer::addToCart(Fragrance* f) {
    if (!f) return false;
    if (f->getQuantity() == 0) return false;
    cart.addItem(f);
    return true;
}

bool Buyer::removeFromCart(const std::string& name) {
    return cart.removeItem(name);
}

void Buyer::viewCart() const {
    cart.show();
}

void Buyer::addPurchase(const Purchase& p) { purchases.push_back(p); }

void Buyer::viewBought() const {
    bool any = false;
    for (const auto& p : purchases) {
        if (p.getStatus() == PurchaseStatus::DELIVERED) { p.show(); any = true; }
    }
    if (!any) std::cout << " No delivered purchases.\n";
}

void Buyer::viewPurchases() const {
    if (purchases.empty()) { std::cout << " No purchases yet.\n"; return; }
    for (const auto& p : purchases) p.show();
}

void Buyer::addDiscount(Discount* d) { discounts.push_back(d); }

Discount* Buyer::pickBestDiscount() const {
    if (discounts.empty()) return nullptr;
    const auto& items = cart.getItems();
    double normalTotal = cart.getTotal();

    Discount* best = nullptr;
    double    saved = 0;
    for (auto* d : discounts) {
        double after = d->apply(items);
        double saving = normalTotal - after;
        if (saving > saved) { saved = saving; best = d; }
    }
    return best;  
}

void Buyer::removeDiscount(Discount* d) {
    for (size_t i = 0; i < discounts.size(); ++i) {
        if (discounts[i] == d) {
            delete discounts[i];
            discounts.erase(discounts.begin() + i);
            return;
        }
    }
}

