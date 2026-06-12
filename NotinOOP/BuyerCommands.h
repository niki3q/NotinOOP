#pragma once
#include "CommandRouter.h"

class BuyerCommands {
private:
    CommandRouter& sys;

    Buyer* buyer();

    void giveRandomDiscount(Buyer* b);

public:
    explicit BuyerCommands(CommandRouter& sys);

    void addToBalance(double amount);
    void addToCart(const std::string& name);
    void removeFromCart(const std::string& name);
    void viewCart();
    void addToWishlist(const std::string& name);
    void removeFromWishlist(const std::string& name);
    void recommend();
    void checkout();
    void cancel(int purchaseId);
    void viewBought();
    void viewPurchases();
    void makeReview(const std::string& fragName, double rating, const std::string& comment);
};
