#pragma once
#include <string>
#include <vector>
#include "Fragrance.h"

enum class DiscountType 
{
	BASE,
	BONUS,
	BRAND
};
class Discount
{
protected:
	static int nextId;
	int discountId;
	double discountPercentage;

public:
	explicit Discount(double percent);
	Discount(int id, double percent);
	virtual ~Discount() = default;

	int getId() const;
	double getPercent() const;
	virtual double apply(const std::vector<Fragrance*>& items) const;
	virtual double savings(const std::vector<Fragrance*>& items) const;
	virtual DiscountType getType() const;
	virtual std::string  describe() const;

	static int getNextId(); 
};

