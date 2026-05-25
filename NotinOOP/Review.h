#pragma once
#include <string>

class Review
{
private:
	static int nextId;
	int reviewId;
	int userId;
	std::string fragranceName;
	std::string comment;
	double rating;

public:
	Review(int rId, int uId, const std::string& fragName, const std::string& comm, double rate);

	int getReviewId() const;
	int getUserId() const;
	const std::string& getFragranceName() const;
	const std::string& getComment() const;
	double getRating() const;

	std::string toString() const;

	std::string save() const;

};

