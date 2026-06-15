#pragma once
#include <string>
#include <iostream>

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
	Review(int userId, const std::string& fragranceName, double rating, const std::string& comment);
	Review(int id, int userId, const std::string& fragranceName, double rating, const std::string& comment);

	int getReviewId() const;
	int getUserId() const;
	const std::string& getFragranceName() const;
	const std::string& getComment() const;
	double getRating() const;

	std::string toString() const;

	void show() const;
	std::string save() const;

	static void setNextId(int id) { if (id >= nextId) nextId = id + 1; }
	static int  getNextId() { return nextId; }
};

