#pragma once
#include "CommandRouter.h"

class AdminCommands {
private:
    CommandRouter& sys;

public:
    explicit AdminCommands(CommandRouter& sys);

    void blockUser(const std::string& username);
    void createFragrance(const std::string& name, const std::string& brand,double price, const std::string& family);
    void addQuantity(const std::string& name, int qty);
    void deliver(int purchaseId);
    void removeReview(int fragranceId, int reviewId);  

    void createAdmin(const std::string& username, const std::string& password);
    void showUndeliveredPurchases();
    void viewAllReviews();

};