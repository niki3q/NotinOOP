#include "BonusDiscount.h"

BonusDiscount::BonusDiscount(double percent, double bonus)
    : Discount(percent), bonus(bonus) {
}

BonusDiscount::BonusDiscount(int id, double percent, double bonus)
    : Discount(id, percent), bonus(bonus) {
}

double BonusDiscount::apply(const std::vector<Fragrance*>& items) const {
    double afterPercent = Discount::apply(items);
    double result = afterPercent - bonus;
    return result < 0 ? 0.0 : result;
}

double BonusDiscount::savings(const std::vector<Fragrance*>& items) const {
    double total = 0;
    for (auto* f : items) total += f->getPrice();
    return total - apply(items);
}


std::string BonusDiscount::describe() const {
    return std::to_string((int)discountPercentage) + "% off + $"
        + std::to_string((int)bonus) + " bonus deduction";
}

double BonusDiscount::getBonus() const
{
	return bonus;
}

DiscountType BonusDiscount::getType() const
{
	return DiscountType::BONUS; 
}
