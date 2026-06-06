// NotinOOP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Admin.h"
#include <iostream>

int main()
{
    Admin adminUser("admin1", "super_secret_fmi");

    std::cout << "User type: " << adminUser.getType() << "\n";

    if (adminUser.isAdmin()) {
        std::cout << "Access Granted: Welcome to the Admin Panel, " << adminUser.getUsername() << "!\n\n";
    }

    adminUser.showHelp();

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
