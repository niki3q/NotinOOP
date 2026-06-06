#pragma once
#include "Discount.h"
class BrandDiscount : public Discount
{
private:
	Brand brand;

public:
    BrandDiscount(double percent, Brand brand);
    BrandDiscount(int id, double percent, Brand brand);

    Brand getBrand() const;

    double apply(const std::vector<Fragrance*>& items) const override;
    double savings(const std::vector<Fragrance*>& items) const override;
    DiscountType getType() const override;
    std::string describe() const override;
};

