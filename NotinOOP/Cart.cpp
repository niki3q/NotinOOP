#include "Cart.h"
#include "Fragrance.h"
#include <iostream>

void Cart::addItem(Fragrance* f) {
    items.push_back(f);
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
    for (auto* f : items)
        std::cout << " - " << f->getName()
        << " $" << f->getPrice() << "\n";
    std::cout << " Total: $" << getTotal() << "\n";
}