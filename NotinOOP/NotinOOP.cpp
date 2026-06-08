// NotinOOP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Admin.h"
#include "Buyer.h"
#include "Cart.h"
#include "Fragrance.h"
#include "BonusDiscount.h"
#include "BrandDiscount.h"
#include <iostream>

int main()
{
    Admin admin("admin_user", "admin123");
    Buyer buyer("buyer_petko", "petko123petko");

    Fragrance f1("XERJOFF", Brand::XERJOFF, 100.0, FragranceFamily::WOODY, 5);
    Fragrance f2("LATAFFA", Brand::LATAFFA, 120.0, FragranceFamily::ORIENTAL, 2);

    buyer.addToBalance(300.0);
    buyer.addToCart(&f1);
    buyer.addToCart(&f2);

    std::cout << "Initial total: $" << buyer.getCart().getTotal() << "\n";

    Discount* d1 = new BrandDiscount(10.0, Brand::XERJOFF);
    Discount* d2 = new BonusDiscount(5.0, 15.0);

    buyer.addDiscount(d1);
    buyer.addDiscount(d2);

    Discount* best = buyer.pickBestDiscount();
    std::cout << "Selected discount: " << best->describe() << "\n";

    double finalPrice = best->apply(buyer.getCart().getItems());
    std::cout << "Final checkout price: $" << finalPrice << "\n";

    buyer.deductBalance(finalPrice);
    buyer.removeDiscount(best);

    std::cout << "Remaining vouchers: " << buyer.getDiscounts().size() << "\n";

    buyer.getCart().clear();
    std::cout << "Checkout verified.\n\n";

    std::cout << "Simulating review moderation...\n";

    for (int i = 0; i < 6; ++i) {
        buyer.incrementRemovedReviews();
    }

    buyer.incrementRemovedReviews();

    std::cout << "Removed reviews count: " << buyer.getRemovedReviews() << "\n";
    std::cout << "Account blocked status: " << (buyer.isBlocked() ? "TRUE" : "FALSE") << "\n";

    std::cout << "Automated restriction verified.\n\n";

    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
