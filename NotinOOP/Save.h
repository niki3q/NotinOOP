#pragma once
#include "Buyer.h"
#include "Admin.h"
#include "Fragrance.h"
#include "Purchase.h"
#include <vector>
#include <string>

class Save {
public:
    static void toFile(const std::string& filename,
        const std::vector<User*>& users,
        const std::vector<Fragrance>& fragrances,
        const std::vector<Purchase>& purchases);
};