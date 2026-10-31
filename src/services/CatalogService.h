#ifndef CATALOGSERVICE_H
#define CATALOGSERVICE_H

#include "repository/IItemRepository.h"
#include "services/ICatalogService.h"

// Dedicated service for Library Catalog & Item Inventory management.
class CatalogService : public ICatalogService {
public:
    explicit CatalogService(IItemRepository& items);

    OperationResult addItem(ItemFactory::ItemType type, const std::string& title,
                            const std::string& author, int catalogId, int extraNumeric) override;
    OperationResult editItem(int catalogId, const std::string& newTitle, const std::string& newAuthor) override;
    LibraryItem* findItem(int catalogId) override;
    std::vector<LibraryItem*> listAllItems() override;
    std::vector<LibraryItem*> listAvailableItems() override;

private:
    IItemRepository& items_;
};

#endif // CATALOGSERVICE_H

