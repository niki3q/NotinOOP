#pragma once
#include "Buyer.h"
#include "Admin.h"
#include "Fragrance.h"
#include "Purchase.h"
#include "BonusDiscount.h"
#include "BrandDiscount.h"
#include <vector>
#include <string>

class Database {
public:
    static void load(const std::string& filename,
        std::vector<User*>& users,
        std::vector<Fragrance>& fragrances,
        std::vector<Purchase>& purchases);

    static void save(const std::string& filename,
        const std::vector<User*>& users,
        const std::vector<Fragrance>& fragrances,
        const std::vector<Purchase>& purchases);

private:
    static std::vector<std::string> split(const std::string& s, char delim);
};

