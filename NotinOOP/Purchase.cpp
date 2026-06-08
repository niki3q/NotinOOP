#include "Purchase.h"
#include <iostream>

int Purchase::nextId = 1;

Purchase::Purchase()
	:purchaseId(0), userId(0), totalPrice(0), status(PurchaseStatus::PENDING)
{
}

Purchase::Purchase(int userId, const std::vector<Fragrance*>& items, double price)
    : purchaseId(nextId++), userId(userId), totalPrice(price), status(PurchaseStatus::PENDING) {
    for (auto* f : items) fragranceNames.push_back(f->getName());
}


int Purchase::getPurchaseId() const 
{ 
    return purchaseId; 
}
int Purchase::getUserId() const 
{
    return userId; 
}
PurchaseStatus Purchase::getStatus() const 
{ 
    return status;
}
double Purchase::getTotalPrice() const 
{ 
    return totalPrice;
}
const std::vector<std::string>& Purchase::getFragranceNames() const
{
    return fragranceNames;
}

void Purchase::setStatus(PurchaseStatus s)
{
    status = s;
}

void Purchase::setNextId(int id) 
{ 
    nextId = id;
}
int Purchase::getNextId() 
{ 
    return nextId;
}

void  Purchase::show() const {
    std::cout << "  Purchase #" << userId
        << "[" << purchaseId << "]"
        << " total:$ " << totalPrice << "\n"
        << " items: ";
    for (size_t i = 0; i < fragranceNames.size(); ++i) {
        std::cout << fragranceNames[i];
        if (i + 1 < fragranceNames.size()) std::cout << ", ";
    }
    std::cout << "\n";
}

