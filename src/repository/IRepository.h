#ifndef IREPOSITORY_H
#define IREPOSITORY_H

#include <functional>
#include <vector>

// Minimal storage abstraction. LibraryService depends on this interface,
// not on a concrete container, so a different backing store (e.g. a file-
// based repository) can be swapped in later without changing LibraryService.
template <typename T>
class IRepository {
public:
    virtual ~IRepository() = default;

    virtual void add(const T& item) = 0;
    virtual T* find(const std::function<bool(const T&)>& predicate) = 0;
    virtual std::vector<T>& all() = 0;
    virtual size_t count() const = 0;
};

#endif
