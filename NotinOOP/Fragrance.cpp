#include "Fragrance.h"
//#include <stdexpect>
#include <iostream>

int Fragrance::nextId = 1;

Fragrance::Fragrance() 
	:fragranceId(0), brand(Brand::UNKNOWN), price(0), 
	family(FragranceFamily::UNDISCLOSED), quantity(0)
{}

Fragrance::Fragrance(const std::string& fragranceName, Brand brand, double price, FragranceFamily family, int quantity)
:fragranceId(nextId++), fragranceName(fragranceName), brand(brand), price(price),
family(family), quantity(quantity){}


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
const std::vector<Review>  Fragrance::getReviews() const {
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

}

void Fragrance::addReview(const Review& newReview) {

}
bool Fragrance::removeReview(int reviewId) {

}

const Review* Fragrance::findReview(int reviewId) const {

}
static void resetCounter(int value) {

}
static int  getNextId() {

}