#include "Review.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

int Review::nextId = 1;

Review::Review(int rId, int uId, const std::string& fragName, const std::string& comm, double rate)
	:reviewId(nextId++), userId(uId), fragranceName(fragName), comment(comm), rating(rate)
{
	if (rating < 0 || rating > 5) {
		throw std::invalid_argument("Rating should be a number between 0 and 5");
	}
	if (comment.size() > 1000) {
		throw std::invalid_argument("The comment can't exceed 1000 characters");
	}
}

int Review::getReviewId() const
{
	return reviewId;
}

int Review::getUserId() const
{
	return userId;
}

const std::string& Review::getFragranceName() const
{
	return fragranceName;
}

const std::string& Review::getComment() const
{
	return comment;
}

double Review::getRating() const
{
	return rating;
}

std::string Review::toString() const
{
	return "REVIEW|" + std::to_string(reviewId) + "|" + std::to_string(userId) + "|" +
		fragranceName + "|" + std::to_string(rating) + "|" + comment;
}

void Review::show() const {
	std::cout << " [Review #" << reviewId << "] "
		<< rating << "/5  \"" << comment
		<< "\"  (user #" << userId << ")\n";
}

std::string Review::save() const
{
	std::ostringstream oss;
	oss << reviewId << "|" << fragranceName << "|"
		<< userId << "|" << rating << "|" << comment;
	return oss.str();
}
