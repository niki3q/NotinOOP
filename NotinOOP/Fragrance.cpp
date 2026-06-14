#include "Fragrance.h"
//#include <stdexpect>
#include <iostream>
#include <sstream>
#include <iomanip>

int Fragrance::nextId = 1;

Fragrance::Fragrance() 
	:fragranceId(0), brand(Brand::UNKNOWN), family(FragranceFamily::UNDISCLOSED), price(0), quantity(0)
{}

Fragrance::Fragrance(const std::string& fragranceName, Brand brand, double price, FragranceFamily family, int quantity)
	:fragranceId(nextId++), fragranceName(fragranceName), brand(brand), family(family), price(price), quantity(quantity) 
{}

Fragrance::Fragrance(int id, const std::string& name, Brand brand, double price, FragranceFamily family, int quantity)
	: fragranceId(id), fragranceName(name), brand(brand), family(family), price(price), quantity(quantity)
{
	if (id >= nextId) nextId = id + 1;
}

int Fragrance::getFragranceId() const {
	return fragranceId;
}

const std::string& Fragrance::getName() const {
	return fragranceName;
}

Brand Fragrance::getBrand() const {
	return brand;
}

FragranceFamily Fragrance::getFamily() const {
	return family;
}

double Fragrance::getPrice() const {
	return price;
}

int Fragrance::getQuantity() const {
	return quantity;
}
const std::vector<Review>& Fragrance::getReviews() const {
	return reviews;
}

void Fragrance::addQuantity(int quant) {
	if(quant < 0) throw std::invalid_argument("Quantity cannot be negative.");
	quantity += quant;
}

bool Fragrance::reduceQuantity() {
	if (quantity <= 0) throw std::invalid_argument("Quantity is already at 0.");;
	quantity--;
	return true;
}
double Fragrance::getRating() const {
	if (reviews.empty()) return 0.0;
	double sum = 0.0;
	for (const auto& r : reviews) {
		sum += r.getRating();
	}

	return sum / reviews.size();
}

void Fragrance::addReview(const Review& newReview) {
	reviews.push_back(newReview);
}

bool Fragrance::removeReview(int reviewId) {
	if (reviews.empty()) {
		throw std::runtime_error("Cannot remove review: No reviews available for fragrance '"
			+ fragranceName + "'");
	}

	auto it = std::find_if(reviews.begin(), reviews.end(),
		[reviewId](const Review& r) {
			return r.getReviewId() == reviewId;
		});

	if (it == reviews.end()) {
		throw std::invalid_argument("Review with ID " + std::to_string(reviewId)
			+ " not found in fragrance '" + fragranceName + "'");
	}

	reviews.erase(it);

	std::cout << "Review #" << reviewId << " successfully removed from '"
		<< fragranceName << "'.\n";
	return true;
}

const Review* Fragrance::findReview(int reviewId) const {
	if (reviews.empty()) {
		throw std::runtime_error("Cannot find review: No reviews available for fragrance '"
			+ fragranceName + "' (ID: " + std::to_string(fragranceId) + ")");
	}

	auto it = std::find_if(reviews.begin(), reviews.end(),
		[reviewId](const Review& r) {
			return r.getReviewId() == reviewId;
		});

	if (it == reviews.end()) {
		throw std::invalid_argument("Review with ID " + std::to_string(reviewId)
			+ " not found in fragrance '" + fragranceName + "'");
	}

	return &(*it);
}

int Fragrance::countReviewsByUser(int userId) const
{
	int count = 0;
	for (const auto& r : reviews) {
		if (r.getUserId() == userId) count++;
	}
	return count;
}

void Fragrance::show() const {
	std::cout << "  | "
		<< std::left << std::setw(2) << fragranceId << " | "
		<< std::left << std::setw(20) << fragranceName << " | "
		<< std::left << std::setw(10) << brandToString(brand) << " | "
		<< std::left << std::setw(9) << familyToString(family) << " | "
		<< "$" << std::left << std::setw(5) << (int)price << " | "
		<< std::left << std::setw(5) << quantity << " | "
		<< std::fixed << std::setprecision(1) << getRating() << "    |\n";
}