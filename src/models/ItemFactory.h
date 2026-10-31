#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <memory>
#include <string>

#include "LibraryItem.h"

// Factory pattern: centralizes construction of LibraryItem subtypes so
// callers (LibraryService) never call `new Book(...)`/`new DVD(...)`
// directly. Adding a 4th item type means adding one case here -- the
// known OCP caveat of a plain factory function (a self-registering
// factory map would close that gap, not built here to avoid over-
// engineering beyond what's needed for this demo).
class ItemFactory {
public:
    enum class ItemType { Book, Dvd, Magazine };

    // extraNumeric: runtime minutes for Dvd, issue number for Magazine,
    // ignored for Book.
    static std::unique_ptr<LibraryItem> create(ItemType type, const std::string& title,
                                                 const std::string& author, int catalogId, int extraNumeric);
};

#endif
