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
    std::cout << "\n"
        << "  *-------------------------------------------------------------*\n"
        << "  |                     Buyer Commands                          |\n"
        << "  |-------------------------------------------------------------|\n"
        << "  | add-to-balance <amount>  | top up your balance              |\n"
        << "  | show-balance             | display your current balance     |\n"
        << "  | add-to-cart <name>       | add fragrance to cart            |\n"
        << "  | remove-from-cart <name>  | remove from cart                 |\n"
        << "  | view-cart                | show current cart                |\n"
        << "  | add-to-wishlist <name>   | save to wishlist                 |\n"
        << "  | remove-from-wishlist <n> | remove from wishlist             |\n"
        << "  | recommend                | get recommendations              |\n"
        << "  | checkout                 | place order (best voucher auto)  |\n"
        << "  | cancel <purchase-id>     | cancel a PENDING order           |\n"
        << "  | view-purchases           | show all your orders             |\n"
        << "  | view-bought              | show delivered orders only       |\n"
        << "  | make-review <n> <r> <c>  | review a fragrance (0-5 stars)   |\n"
        << "  | list-fragrances          | browse the catalogue             |\n"
        << "  | logout                   | leave account                    |\n"
        << "  | help                     | show this menu                   |\n"
        << "  *-------------------------------------------------------------*\n\n";
}

void Buyer::addToBalance(double amount)
{
    if (amount > 0) balance += amount;
}

bool Buyer::deductBalance(double amount) {
    if (balance < amount) return false;
    balance -= amount;
    return true;
}

void Buyer::showBalance() const {
    std::cout << "  Balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
}

bool Buyer::addToWishlist(const std::string& name) {
    if (isInWishlist(name)) return false;
    wishlist.push_back(name);
    return true;
}

bool Buyer::removeFromWishlist(const std::string& name) {
    auto it = std::find(wishlist.begin(), wishlist.end(), name);
    if (it != wishlist.end()) {
        wishlist.erase(it);
        return true;
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

bool Buyer::removeFromCart(const std::string& name)
{
    return cart.removeItem(name);
}

void Buyer::viewCart() const {
    cart.show();
}

void Buyer::addPurchase(const Purchase& p)
{
    purchases.push_back(p);
}

void Buyer::viewBought() const
{
    bool any = false;
    for (const auto& p : purchases) {
        if (p.getStatus() == PurchaseStatus::DELIVERED)
        {
            p.show(); any = true;
        }
    }
    if (!any) std::cout << " No delivered purchases.\n";
}

void Buyer::viewPurchases() const
{
    if (purchases.empty())
    {
        std::cout << " No purchases yet.\n"; return;
    }
    for (const auto& p : purchases) p.show();
}

void Buyer::addDiscount(Discount* d)
{
    if (d) discounts.push_back(d);
}

Discount* Buyer::pickBestDiscount() const
{
    if (discounts.empty() || cart.isEmpty()) return nullptr;
    double normalTotal = cart.getTotal();
    Discount* best = nullptr;
    double bestSaving = 0;
    for (auto* d : discounts) {
        double saving = normalTotal - d->apply(cart.getItems());
        if (saving > bestSaving) { bestSaving = saving; best = d; }
    }
    return best;
}

void Buyer::removeDiscount(Discount* d)
{
    for (size_t i = 0; i < discounts.size(); ++i) {
        if (discounts[i] == d) {
            delete discounts[i];
            discounts.erase(discounts.begin() + i);
            return;
        }
    }
}

void Buyer::incrementRemovedReviews()
{
    removedReviews++;
    if (removedReviews >= 7) {
        setBlocked(true);
    }
}

