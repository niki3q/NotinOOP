#pragma once
#include "Discount.h"

class BonusDiscount : public Discount
{
private:
	double bonus;

public:
	BonusDiscount(double percent, double bonus);
	BonusDiscount(int id, double percent, double bonus);

	double getBonus() const;

	double apply(const std::vector<Fragrance*>& items) const override;
	double savings(const std::vector<Fragrance*>& items) const override;
	DiscountType getType() const override;
	std::string  describe() const override;
};

