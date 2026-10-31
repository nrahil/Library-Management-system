#ifndef INMEMORYITEMREPOSITORY_H
#define INMEMORYITEMREPOSITORY_H

#include "IItemRepository.h"

class InMemoryItemRepository : public IItemRepository {
public:
    void add(std::unique_ptr<LibraryItem> item) override {
        items_.push_back(std::move(item));
    }

    LibraryItem* find(const std::function<bool(const LibraryItem&)>& predicate) override {
        for (auto& item : items_) {
            if (predicate(*item)) {
                return item.get();
            }
        }
        return nullptr;
    }

    std::vector<LibraryItem*> allRaw() override {
        std::vector<LibraryItem*> raw;
        raw.reserve(items_.size());
        for (auto& item : items_) {
            raw.push_back(item.get());
        }
        return raw;
    }

    size_t count() const override {
        return items_.size();
    }

private:
    std::vector<std::unique_ptr<LibraryItem>> items_;
};

#endif
