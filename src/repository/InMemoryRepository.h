#ifndef INMEMORYREPOSITORY_H
#define INMEMORYREPOSITORY_H

#include "IRepository.h"

template <typename T>
class InMemoryRepository : public IRepository<T> {
public:
    void add(const T& item) override {
        items_.push_back(item);
    }

    T* find(const std::function<bool(const T&)>& predicate) override {
        for (auto& item : items_) {
            if (predicate(item)) {
                return &item;
            }
        }
        return nullptr;
    }

    std::vector<T>& all() override {
        return items_;
    }

    size_t count() const override {
        return items_.size();
    }

private:
    std::vector<T> items_;
};

#endif
