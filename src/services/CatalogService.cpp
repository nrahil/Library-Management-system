#include "services/CatalogService.h"

#include "events/NotificationCenter.h"

CatalogService::CatalogService(IItemRepository& items) : items_(items) {}

LibraryItem* CatalogService::findItem(int catalogId) {
    return items_.find([catalogId](const LibraryItem& item) { return item.getCatalogId() == catalogId; });
}

std::vector<LibraryItem*> CatalogService::listAvailableItems() {
    std::vector<LibraryItem*> available;
    for (LibraryItem* item : items_.allRaw()) {
        if (item->isAvailable()) {
            available.push_back(item);
        }
    }
    return available;
}

OperationResult CatalogService::addItem(ItemFactory::ItemType type, const std::string& title,
                                         const std::string& author, int catalogId, int extraNumeric) {
    if (findItem(catalogId) != nullptr) {
        return {false, "An item with this catalog ID already exists."};
    }

    auto item = ItemFactory::create(type, title, author, catalogId, extraNumeric);
    std::string description = item->describe();
    items_.add(std::move(item));

    NotificationCenter::instance().publish({EventType::ItemAdded, "Item added: " + description});

    return {true, "Item added."};
}

OperationResult CatalogService::editItem(int catalogId, const std::string& newTitle, const std::string& newAuthor) {
    LibraryItem* item = findItem(catalogId);
    if (item == nullptr) {
        return {false, "Item not found."};
    }

    item->setTitle(newTitle);
    item->setAuthor(newAuthor);
    return {true, "Item details updated."};
}

std::vector<LibraryItem*> CatalogService::listAllItems() {
    return items_.allRaw();
}

