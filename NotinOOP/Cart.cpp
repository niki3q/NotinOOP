#include "Cart.h"
#include "Fragrance.h"
#include <iostream>
#include <iomanip>

void Cart::addItem(Fragrance* f) {
    if (f) items.push_back(f);
}

bool Cart::removeItem(const std::string& name) {
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i]->getName() == name) {
            items.erase(items.begin() + i);
            return true;
        }
    }
    return false;
}

void Cart::clear() {
    items.clear();
}

bool Cart::isEmpty() const { 
    return items.empty(); 
}

const std::vector<Fragrance*>& Cart::getItems() const {
    return items; 
}

double Cart::getTotal() const {
    double total = 0;
    for (auto* f : items) total += f->getPrice();
    return total;
}

void Cart::show() const {
    if (items.empty()) {
        std::cout << "  (cart is empty)\n";
        return;
    }

    std::cout << "\n";
    std::cout << "  +------------------------------+----------+\n";
    std::cout << "  | Fragrance                    |    Price |\n";
    std::cout << "  +------------------------------+----------+\n";
    for (auto* f : items) {
        std::cout << "  | " << std::left << std::setw(28) << f->getName()
            << " | $" << std::right << std::setw(7) << f->getPrice() << " |\n";
    }
    std::cout << "  +------------------------------+----------+\n";
    std::cout << "  | " << std::left << std::setw(28) << "Total"
        << " | $" << std::right << std::setw(7) << getTotal() << " |\n";
    std::cout << "  +------------------------------+----------+\n\n";
}