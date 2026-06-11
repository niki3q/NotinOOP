#include "Discount.h"

int Discount::nextId = 1;


Discount::Discount(double percent)
    : discountId(nextId++), discountPercentage(percent) {
}

Discount::Discount(int id, double percent)
    : discountId(id), discountPercentage(percent)
{
    if (id >= nextId) nextId = id + 1;
}

double Discount::apply(const std::vector<Fragrance*>& items) const {
    double total = 0;
    for (auto* f : items) total += f->getPrice();
    return total * (1.0 - discountPercentage / 100.0);
}

double Discount::savings(const std::vector<Fragrance*>& items) const {
    double total = 0;
    for (auto* f : items) total += f->getPrice();
    return total - apply(items);
}

std::string Discount::describe() const {
    return std::to_string((int)discountPercentage) + "% off everything";
}

int Discount::getId() const 
{
	return discountId; 
}
double Discount::getPercent() const
{ 
	return discountPercentage; 
}

DiscountType  Discount::getType()  const
{
	return DiscountType::BASE; 
}

int Discount::getNextId() 
{
	return nextId;
}

void Discount::setNextId(int id)
{ 
    if (id >= nextId) nextId = id + 1; 
}