#include "Review.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

int Review::nextId = 1;

Review::Review(int userId, const std::string& fragranceName,
	double rating, const std::string& comment)
	: reviewId(nextId++), userId(userId),
	fragranceName(fragranceName), comment(comment), rating(rating)
{
	if (rating < 0 || rating > 5)
		throw std::invalid_argument("Rating must be between 0 and 5.");
	if (comment.size() > 1000)
		throw std::invalid_argument("Comment cannot exceed 1000 characters.");
}

Review::Review(int id, int userId, const std::string& fragranceName,
	double rating, const std::string& comment)
	: reviewId(id), userId(userId),
	fragranceName(fragranceName), comment(comment), rating(rating)
{
	if (id >= nextId) nextId = id + 1;
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
	// format:  id|userId|fragranceName|rating|comment
	std::ostringstream oss;
	oss << reviewId << "|" << userId << "|"
		<< fragranceName << "|" << rating << "|" << comment;
	return oss.str();
}
