#pragma once
#include "Buyer.h"
#include "Admin.h"
#include "Fragrance.h"
#include "Purchase.h"
#include <vector>
#include <string>

class Load {
public:
    static void fromFile(const std::string& filename,
        std::vector<User*>& users,
        std::vector<Fragrance>& fragrances,
        std::vector<Purchase>& purchases);

private:
    static std::vector<std::string> split(const std::string& s, char delim);
};
