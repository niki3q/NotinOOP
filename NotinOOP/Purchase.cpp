#include "Purchase.h"
#include <iostream>
#include <iomanip>

int Purchase::nextId = 1;

Purchase::Purchase()
	:purchaseId(0), userId(0), totalPrice(0), status(PurchaseStatus::PENDING)
{
}

Purchase::Purchase(int userId, const std::vector<Fragrance*>& items, double price)
    : purchaseId(nextId++), userId(userId), totalPrice(price), status(PurchaseStatus::PENDING) 
{
    for (auto* f : items) fragranceNames.push_back(f->getName());
}

Purchase::Purchase(int id, int userId, PurchaseStatus status,
    double totalPrice, const std::vector<std::string>& names)
    : purchaseId(id), userId(userId), fragranceNames(names),
    status(status), totalPrice(totalPrice)
{
    if (id >= nextId) nextId = id + 1;
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
    std::string statusDisplay;
    if (status == PurchaseStatus::DELIVERED) statusDisplay = "[DELIVERED]";
    else if (status == PurchaseStatus::CANCELED)  statusDisplay = "[CANCELED] ";
    else                                           statusDisplay = "[PENDING]  ";

    std::cout << "\n";
    std::cout << "  +-----------------------------------------+\n";
    std::cout << "  | Purchase #" << std::left << std::setw(4) << purchaseId
        << "  " << statusDisplay
        << "  $" << std::right << std::setw(8) << std::fixed
        << std::setprecision(2) << totalPrice << " |\n";
    std::cout << "  | Items: ";
    for (size_t i = 0; i < fragranceNames.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << fragranceNames[i];
    }
    std::cout << "\n";
    std::cout << "  +-----------------------------------------+\n";
}

