#pragma once
#include <string>

enum class Brand {
    DIOR, ARMANI, LATAFFA, YSL, MANCERA,
    GUCCI, BOSS, PRADA, MONTALE, LANCOME,
    AZZARO, MONTBLANC, GUESS, XERJOFF, UNKNOWN
};

inline std::string brandToString(Brand b) {
    switch (b) {
    case Brand::DIOR:      return "DIOR";
    case Brand::ARMANI:    return "ARMANI";
    case Brand::LATAFFA:   return "LATAFFA";
    case Brand::YSL:       return "YSL";
    case Brand::MANCERA:   return "MANCERA";
    case Brand::GUCCI:     return "GUCCI";
    case Brand::BOSS:      return "BOSS";
    case Brand::PRADA:     return "PRADA";
    case Brand::MONTALE:   return "MONTALE";
    case Brand::LANCOME:   return "LANCOME";
    case Brand::AZZARO:    return "AZZARO";
    case Brand::MONTBLANC: return "MONTBLANC";
    case Brand::GUESS:     return "GUESS";
    case Brand::XERJOFF:   return "XERJOFF";
    default:               return "UNKNOWN";
    }
}

inline Brand brandFromString(const std::string& s) {
    if (s == "DIOR")      return Brand::DIOR;
    if (s == "ARMANI")    return Brand::ARMANI;
    if (s == "LATAFFA")   return Brand::LATAFFA;
    if (s == "YSL")       return Brand::YSL;
    if (s == "MANCERA")   return Brand::MANCERA;
    if (s == "GUCCI")     return Brand::GUCCI;
    if (s == "BOSS")      return Brand::BOSS;
    if (s == "PRADA")     return Brand::PRADA;
    if (s == "MONTALE")   return Brand::MONTALE;
    if (s == "LANCOME")   return Brand::LANCOME;
    if (s == "AZZARO")    return Brand::AZZARO;
    if (s == "MONTBLANC") return Brand::MONTBLANC;
    if (s == "GUESS")     return Brand::GUESS;
    if (s == "XERJOFF")   return Brand::XERJOFF;
    return Brand::UNKNOWN;
}

enum class FragranceFamily {
    FLORAL, CITRUS, GREEN, AQUATIC, FRUITY,
    SPICY, WOODY, GOURMAND, ORIENTAL, ANIMALIC, UNDISCLOSED
};

inline std::string familyToString(FragranceFamily f) {
    switch (f) {
    case FragranceFamily::FLORAL:      return "FLORAL";
    case FragranceFamily::CITRUS:      return "CITRUS";
    case FragranceFamily::GREEN:       return "GREEN";
    case FragranceFamily::AQUATIC:     return "AQUATIC";
    case FragranceFamily::FRUITY:      return "FRUITY";
    case FragranceFamily::SPICY:       return "SPICY";
    case FragranceFamily::WOODY:       return "WOODY";
    case FragranceFamily::GOURMAND:    return "GOURMAND";
    case FragranceFamily::ORIENTAL:    return "ORIENTAL";
    case FragranceFamily::ANIMALIC:    return "ANIMALIC";
    default:                           return "UNDISCLOSED";
    }
}

inline FragranceFamily familyFromString(const std::string& s) {
    if (s == "FLORAL")   return FragranceFamily::FLORAL;
    if (s == "CITRUS")   return FragranceFamily::CITRUS;
    if (s == "GREEN")    return FragranceFamily::GREEN;
    if (s == "AQUATIC")  return FragranceFamily::AQUATIC;
    if (s == "FRUITY")   return FragranceFamily::FRUITY;
    if (s == "SPICY")    return FragranceFamily::SPICY;
    if (s == "WOODY")    return FragranceFamily::WOODY;
    if (s == "GOURMAND") return FragranceFamily::GOURMAND;
    if (s == "ORIENTAL") return FragranceFamily::ORIENTAL;
    if (s == "ANIMALIC") return FragranceFamily::ANIMALIC;
    return FragranceFamily::UNDISCLOSED;
}

enum class PurchaseStatus {
    PENDING,
    DELIVERED,
    CANCELED
};

inline std::string statusToString(PurchaseStatus s) {
    switch (s) {
    case PurchaseStatus::PENDING:   return "PENDING";
    case PurchaseStatus::DELIVERED: return "DELIVERED";
    case PurchaseStatus::CANCELED:  return "CANCELED";
    default:                        return "PENDING";
    }
}

inline PurchaseStatus statusFromString(const std::string& s) {
    if (s == "DELIVERED") return PurchaseStatus::DELIVERED;
    if (s == "CANCELED")  return PurchaseStatus::CANCELED;
    return PurchaseStatus::PENDING;
}

enum class DiscountType {
    BASE,
    BONUS,
    BRAND
};
