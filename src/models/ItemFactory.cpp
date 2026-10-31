#include "ItemFactory.h"

#include "Book.h"
#include "DVD.h"
#include "Magazine.h"

std::unique_ptr<LibraryItem> ItemFactory::create(ItemType type, const std::string& title,
                                                  const std::string& author, int catalogId, int extraNumeric) {
    switch (type) {
        case ItemType::Dvd:
            return std::make_unique<DVD>(title, author, catalogId, extraNumeric);
        case ItemType::Magazine:
            return std::make_unique<Magazine>(title, author, catalogId, extraNumeric);
        case ItemType::Book:
        default:
            return std::make_unique<Book>(title, author, catalogId);
    }
}
