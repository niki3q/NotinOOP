#include "BrandDiscount.h"

BrandDiscount::BrandDiscount(double percent, Brand brand)
    : Discount(percent), brand(brand) {
}

BrandDiscount::BrandDiscount(int id, double percent, Brand brand)
    : Discount(id, percent), brand(brand) {
}

double BrandDiscount::apply(const std::vector<Fragrance*>& items) const {
    double total = 0;
    double factor = 1.0 - (discountPercentage / 100.0);
    for (auto* f : items) {
        if (f->getBrand() == brand)
            total += f->getPrice() * factor;
        else
            total += f->getPrice();
    }
    return total;
}

double BrandDiscount::savings(const std::vector<Fragrance*>& items) const {
    double total = 0;
    for (auto* f : items) total += f->getPrice();
    return total - apply(items);
}


std::string BrandDiscount::describe() const {
    return std::to_string((int)discountPercentage) + "% off "
        + brandToString(brand) + " products";
}
Brand BrandDiscount::getBrand() const
{ 
	return brand;
}

DiscountType BrandDiscount::getType() const
{ 
	return DiscountType::BRAND;
}