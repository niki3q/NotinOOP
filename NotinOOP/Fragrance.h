#pragma once
#include "Enums.h"
#include "Review.h"
#include <string>
#include <vector>
#include <algorithm>

class Fragrance
{
private:
	static int nextId;
	int fragranceId;
	std::string fragranceName;
	Brand brand;
	FragranceFamily family;
	double price;
	int quantity;
	std::vector<Review> reviews;

public:
	Fragrance();
	Fragrance(const std::string& fragranceName, Brand brand, double price, FragranceFamily family, int quantity);

	Fragrance(int id, const std::string& name, Brand brand, double price, FragranceFamily family, int quantity);

	int getFragranceId() const;
	const std::string& getName() const;
	Brand getBrand() const;
	FragranceFamily getFamily() const;
	double getPrice() const;
	int getQuantity() const;
	const std::vector<Review>& getReviews() const;

	void addQuantity(int quant);
	bool reduceQuantity();
	double getRating() const;

	void addReview(const Review& newReview);
	bool removeReview(int reviewId);
	const Review* findReview(int reviewId) const;;
	static int getNextId() { return nextId; }
	static void setNextId(int id) { nextId = id; }
	int countReviewsByUser(int userId) const;

	void show() const;
};

