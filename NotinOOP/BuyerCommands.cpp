#include "BuyerCommands.h"
#include "BonusDiscount.h"
#include "BrandDiscount.h"
#include <iostream>
#include <random>

BuyerCommands::BuyerCommands(CommandRouter& sys) : sys(sys) {}

Buyer* BuyerCommands::buyer() {
    return static_cast<Buyer*>(sys.currentUser);
}

void BuyerCommands::giveRandomDiscount(Buyer* b) {
    static std::mt19937 rng(std::random_device{}());

    int type = rng() % 3;

    if (type == 0) {
        int pct = 5 + rng() % 16;          // 5-20%
        b->addDiscount(new Discount(pct));
        std::cout << "  Voucher: " << pct << "% off your next order!\n";

    }
    else if (type == 1) {
        int pct = 5 + rng() % 11;        // 5-15%
        int bonus = 5 + rng() % 21;        // $5-$25
        b->addDiscount(new BonusDiscount(pct, bonus));
        std::cout << "  Voucher: " << pct << "% off + $" << bonus << " bonus deduction!\n";

    }
    else {
        int pct = 10 + rng() % 21;         // 10-30%

        Brand br = Brand::UNKNOWN;
        if (!sys.fragrances.empty())
            br = sys.fragrances[rng() % sys.fragrances.size()].getBrand();

        b->addDiscount(new BrandDiscount(pct, br));
        std::cout << "  Voucher: " << pct << "% off all "
            << brandToString(br) << " products!\n";
    }
}

void BuyerCommands::addToBalance(double amount) {
    buyer()->addToBalance(amount);
    std::cout << "  New balance: $" << buyer()->getBalance() << "\n";
}

void BuyerCommands::showBalance() {
    buyer()->showBalance();
}

void BuyerCommands::addToCart(const std::string& name) {
    Fragrance* f = sys.findFragrance(name);
    if (!f) { std::cout << "  Fragrance not found.\n"; return; }
    if (f->getQuantity() == 0) { std::cout << "  Out of stock.\n"; return; }
    int inCart = 0;
    for (Fragrance* g : buyer()->getCart().getItems())
         if (g == f) inCart++;
    if (inCart >= f->getQuantity()) {
        std::cout << "  Only " << f->getQuantity()
             << " in stock; you already have that many in your cart.\n";
        return;
        
    }
    buyer()->addToCart(f);
    std::cout << "  '" << name << "' added to cart.\n";
}

void BuyerCommands::removeFromCart(const std::string& name) {
    if (buyer()->removeFromCart(name))
        std::cout << "  '" << name << "' removed from cart.\n";
    else
        std::cout << "  '" << name << "' is not in your cart.\n";
}

void BuyerCommands::viewCart() {
    buyer()->viewCart();
}

void BuyerCommands::addToWishlist(const std::string& name) {
    if (!sys.findFragrance(name)) { std::cout << "  Fragrance not found.\n"; return; }
    if (buyer()->addToWishlist(name))
        std::cout << "  '" << name << "' added to wishlist.\n";
    else
        std::cout << "  Already in wishlist.\n";
}

void BuyerCommands::removeFromWishlist(const std::string& name) {
    if (buyer()->removeFromWishlist(name))
        std::cout << "  '" << name << "' removed from wishlist.\n";
    else
        std::cout << "  Not in wishlist.\n";
}

void BuyerCommands::recommend() {
    const std::vector<std::string>& wl = buyer()->getWishlist();
    if (wl.empty()) {
        std::cout << "  Add fragrances to your wishlist first.\n";
        return;
    }

    std::vector<FragranceFamily> families;
    std::vector<int> counts;

    for (const std::string& name : wl) {
        Fragrance* f = sys.findFragrance(name);
        if (!f) continue;

        FragranceFamily fam = f->getFamily();
        bool found = false;
        for (size_t i = 0; i < families.size(); i++) {
            if (families[i] == fam) { counts[i]++; found = true; break; }
        }
        if (!found) { families.push_back(fam); counts.push_back(1); }
    }

    if (families.empty()) { std::cout << "  Nothing to recommend.\n"; return; }

    FragranceFamily bestFamily = families[0];
    int bestCount = counts[0];
    for (size_t i = 1; i < families.size(); i++) {
        if (counts[i] > bestCount) { bestCount = counts[i]; bestFamily = families[i]; }
    }

    std::vector<Fragrance*> candidates;
    for (Fragrance& f : sys.fragrances) {
        if (f.getFamily() == bestFamily &&
            !buyer()->isInWishlist(f.getName()) &&
            f.getQuantity() > 0)
            candidates.push_back(&f);
    }

    if (candidates.empty()) { std::cout << "  No recommendations available right now.\n"; return; }

    static std::mt19937 rng(std::random_device{}());
    std::shuffle(candidates.begin(), candidates.end(), rng);

    int show = (int)candidates.size() < 3 ? (int)candidates.size() : 3;
    std::cout << "  Recommendations (" << familyToString(bestFamily) << "):\n";
    for (int i = 0; i < show; i++)
        candidates[i]->show();
}

void BuyerCommands::checkout() {
    Buyer* b = buyer();
    if (b->getCart().isEmpty()) { std::cout << "  Your cart is empty.\n"; return; }

    const std::vector<Fragrance*>& items = b->getCart().getItems();
    for (Fragrance* f : items) {
        int wanted = 0;
        for (Fragrance* g : items) if (g == f) wanted++;
        if (wanted > f->getQuantity()) {
            std::cout << "  Not enough stock for '" << f->getName() << "' ("
                 << f->getQuantity() << " available, " << wanted << " in cart).\n";
            return;
            
        }
    }
    double total = b->getCart().getTotal();

    Discount* best = b->pickBestDiscount();
    if (best) {
        double afterDiscount = best->apply(items);
        std::cout << "  Voucher applied: " << best->describe()
            << " (saves $" << (total - afterDiscount) << ")\n";
        total = afterDiscount;
    }

    if (!b->deductBalance(total)) {
        std::cout << "  Not enough balance. Need $" << total
            << ", have $" << b->getBalance() << "\n";
        return;
    }

    for (Fragrance* f : items) f->reduceQuantity();

    Purchase p(b->getUserId(), items, total);
    sys.purchases.push_back(p);
    b->addPurchase(p);

    if (best) b->removeDiscount(best);
    b->getCart().clear();

    std::cout << "  Purchase #" << p.getPurchaseId()
        << " placed! Remaining balance: $" << b->getBalance() << "\n";

    giveRandomDiscount(b);
}

void BuyerCommands::cancel(int purchaseId) {
    Buyer* b = buyer();

    Purchase* gp = sys.findPurchase(purchaseId);
    if (!gp || gp->getUserId() != b->getUserId()) {
        std::cout << "  Purchase not found.\n"; return;
    }
    if (gp->getStatus() != PurchaseStatus::PENDING) {
        std::cout << "  Only PENDING purchases can be cancelled.\n"; return;
    }

    gp->setStatus(PurchaseStatus::CANCELED);
    for (Purchase& p : b->getPurchases()) {
        if (p.getPurchaseId() == purchaseId) {
            p.setStatus(PurchaseStatus::CANCELED);
            break;
        }
    }
    b->addToBalance(gp->getTotalPrice());
    for (const std::string& nm : gp->getFragranceNames()) {
        Fragrance * f = sys.findFragrance(nm);
        if (f) f->addQuantity(1);   
    }
    std::cout << "  Purchase #" << purchaseId << " cancelled. $" << gp->getTotalPrice() << " refunded.\n";
}

void BuyerCommands::viewBought() {
    buyer()->viewBought();
}

void BuyerCommands::viewPurchases() {
    buyer()->viewPurchases();
}

void BuyerCommands::makeReview(const std::string& fragName, double rating, const std::string& comment)
{
    Fragrance* f = sys.findFragrance(fragName);
    if (!f) { std::cout << "  Fragrance not found.\n"; return; }

    int uid = sys.currentUser->getUserId();
    if (f->countReviewsByUser(uid) > 0) {
        std::cout << "  You have already reviewed this fragrance.\n";
        return;
    }

    try {
        f->addReview(Review(uid, fragName, rating, comment));
        std::cout << "  Review added!\n";
    }
    catch (const std::exception& e) {
        std::cout << "  Error: " << e.what() << "\n";
    }
}