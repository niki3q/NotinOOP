// NotinOOP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Admin.h"
#include "Buyer.h"
#include "Fragrance.h"
#include <iostream>

int main()
{
    try {
        Buyer b("ivan", "1234");
        b.addToBalance(200);
        std::cout << "Balance: " << b.getBalance() << "\n";

   
        Fragrance* f1 = new Fragrance(
            "Sauvage",
            Brand::DIOR,                
            120.0,
            FragranceFamily::WOODY,     
            5
        );

        Fragrance* f2 = new Fragrance(
            "Perf2",
            Brand::GUESS,
            150.0,
            FragranceFamily::FLORAL,
            3
        );

        b.addToCart(f1);
        b.addToCart(f2);

        std::cout << "\n--- CART ---\n";
        b.viewCart();

        b.addToWishlist("Sauvage");
        b.addToWishlist("Perf2");

        std::cout << "\n--- WISHLIST ---\n";
        for (const auto& w : b.getWishlist()) {
            std::cout << w << "\n";
        }

        b.removeFromCart("Sauvage");

        std::cout << "\n--- CART AFTER REMOVE ---\n";
        b.viewCart();

        std::cout << "\nReducing quantity...\n";
        f2->reduceQuantity();
        std::cout << "Quantity left: " << f2->getQuantity() << "\n";

        try {
            std::cout << "Rating: " << f2->getRating() << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Expected error: " << e.what() << "\n";
        }

        if (b.deductBalance(50)) {
            std::cout << "Payment OK\n";
        }
        std::cout << "Balance now: " << b.getBalance() << "\n";

        std::cout << "\n--- HELP ---\n";
        b.showHelp();

        delete f1;
        delete f2;
    }
    catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << "\n";
    }

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
