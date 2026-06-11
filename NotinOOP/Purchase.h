#pragma once
#include <string>
#include <vector>
#include "Fragrance.h"
#include "Enums.h"


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
	Purchase(int id, int userId, PurchaseStatus status, double totalPrice, const std::vector<std::string>& names);

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

