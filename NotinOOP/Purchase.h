#pragma once
#include <string>
#include <vector>
#include "Fragrance.h"

enum class PurchaseStatus {
	PENDING,
	DELIVERED,
	CANCELED
};

class Purchase
{
private:
	static int  nextId;
	int purchaseId;
	int userId;
	std::vector<std::string> fragranceNames;
	PurchaseStatus status;
	double totalPrice;

public:
	Purchase();
	Purchase(int userId, const std::vector<Fragrance*>& items, double price);

	int getPurchaseId() const;
	int getUserId() const;
	PurchaseStatus getStatus() const;
	double getTotalPrice() const;
	const std::vector<std::string>& getFragranceNames() const;

	void setStatus(PurchaseStatus s);

	static void setNextId(int id);
	static int getNextId();

	void show() const;
};

