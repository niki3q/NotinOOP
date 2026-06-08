#pragma once
#include "User.h"
#include "Cart.h"
#include "Purchase.h"
#include "Discount.h"
#include "Fragrance.h"
//#include <vector>
//#include <String>

class Buyer : public User
{
    Cart cart;
    std::vector<Purchase> purchases;
    std::vector<std::string> wishlist;       
    double balance;
    std::vector<Discount*> discounts;     
    int removedReviews;

public:
    Buyer(const std::string& username, const std::string& password);
    Buyer(int id, const std::string& username, const std::string& password,
        bool blocked, double balance, int removedReviews);
    Buyer(const Buyer&) = delete;
    Buyer& operator=(const Buyer&) = delete;
    Buyer(Buyer&&) = default;
    Buyer& operator=(Buyer&&) = default;
    ~Buyer() override;


    std::string getRole() const override { return "BUYER"; }
    void showHelp() const override;

    double getBalance() const { return balance; }
    void addToBalance(double amount);
    bool deductBalance(double amount);   

    bool addToWishlist(const std::string& name);          
    bool removeFromWishlist(const std::string& name);    
    bool isInWishlist(const std::string& name) const;
    const std::vector<std::string>& getWishlist() const { return wishlist; }

    Cart& getCart() { return cart; }
    const Cart& getCart() const { return cart; }
    bool addToCart(Fragrance* f);          
    bool removeFromCart(const std::string& name);
    void viewCart() const;

  
    void addPurchase(const Purchase& p);
    std::vector<Purchase>& getPurchases() { return purchases; }
    const std::vector<Purchase>& getPurchases() const { return purchases; }
    void viewBought() const;   
    void viewPurchases() const;   

    void addDiscount(Discount* d);   // takes ownership
    std::vector<Discount*>& getDiscounts() { return discounts; }
    const std::vector<Discount*>& getDiscounts() const { return discounts; }

    Discount* pickBestDiscount() const;

    void removeDiscount(Discount* d);

    int getRemovedReviews()const override { return removedReviews; }
    void incrementRemovedReviews();

  
};

