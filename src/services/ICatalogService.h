#ifndef ICATALOGSERVICE_H
#define ICATALOGSERVICE_H

#include <string>
#include <vector>

#include "common/OperationResult.h"
#include "models/ItemFactory.h"
#include "models/LibraryItem.h"

class ICatalogService {
public:
    virtual ~ICatalogService() = default;

    virtual OperationResult addItem(ItemFactory::ItemType type, const std::string& title,
                                    const std::string& author, int catalogId, int extraNumeric) = 0;
    virtual OperationResult editItem(int catalogId, const std::string& newTitle, const std::string& newAuthor) = 0;
    virtual LibraryItem* findItem(int catalogId) = 0;
    virtual std::vector<LibraryItem*> listAllItems() = 0;
    virtual std::vector<LibraryItem*> listAvailableItems() = 0;
};

#endif // ICATALOGSERVICE_H

