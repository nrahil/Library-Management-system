#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <string>

#include "ItemState.h"

// Abstract base for anything the library lends out. Subclasses (Book, DVD,
// Magazine) add only their own extra fields and describe(); all shared
// behavior (issue/return lifecycle, title/author) lives here so callers
// work through this base pointer and never need to know the concrete type
// (LSP). Availability is delegated to an ItemState (State pattern) instead
// of a bare bool.
class LibraryItem {
public:
    LibraryItem(std::string title, std::string author, int catalogId);
    virtual ~LibraryItem() = default;

    virtual std::string describe() const = 0;

    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    int getCatalogId() const;

    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);

    bool isAvailable() const;
    void issue();
    void returnItem();
    void setState(ItemState& state);

    int issuedToRoll() const;
    void setIssuedToRoll(int roll);

private:
    std::string title_;
    std::string author_;
    int catalogId_;
    ItemState* state_;
    int issuedToRoll_;
};

#endif
