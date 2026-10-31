#ifndef IITEMREPOSITORY_H
#define IITEMREPOSITORY_H

#include <functional>
#include <memory>
#include <vector>

#include "models/LibraryItem.h"

// Separate from the generic IRepository<T> (used for Student): that
// template stores T by value, which can't hold polymorphic LibraryItem
// subtypes. This interface owns items via unique_ptr instead.
class IItemRepository {
public:
    virtual ~IItemRepository() = default;

    virtual void add(std::unique_ptr<LibraryItem> item) = 0;
    virtual LibraryItem* find(const std::function<bool(const LibraryItem&)>& predicate) = 0;
    virtual std::vector<LibraryItem*> allRaw() = 0;
    virtual size_t count() const = 0;
};

#endif
