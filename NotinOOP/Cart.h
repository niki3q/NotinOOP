#pragma once
#include <vector>
#include <string>


class Fragrance;

class Cart {
    std::vector<Fragrance*> items; 

public:
    
    void addItem(Fragrance* f);
    bool removeItem(const std::string& name);   
    void clear();

   
    bool   isEmpty()   const { return items.empty(); }
    double getTotal()  const;
    const std::vector<Fragrance*>& getItems() const { return items; }

    void show() const;
};
