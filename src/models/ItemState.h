#ifndef ITEMSTATE_H
#define ITEMSTATE_H

#include <string>

class LibraryItem;

// State pattern: availability lifecycle for a LibraryItem. Each concrete
// state is stateless, so a single shared instance per state is reused
// across all items (no per-item allocation).
class ItemState {
public:
    virtual ~ItemState() = default;

    virtual bool canIssue() const = 0;
    virtual bool canReturn() const = 0;
    virtual void issue(LibraryItem& item) const = 0;
    virtual void returnItem(LibraryItem& item) const = 0;
    virtual std::string name() const = 0;
};

class AvailableState : public ItemState {
public:
    static ItemState& instance();

    bool canIssue() const override;
    bool canReturn() const override;
    void issue(LibraryItem& item) const override;
    void returnItem(LibraryItem& item) const override;
    std::string name() const override;
};

class IssuedState : public ItemState {
public:
    static ItemState& instance();

    bool canIssue() const override;
    bool canReturn() const override;
    void issue(LibraryItem& item) const override;
    void returnItem(LibraryItem& item) const override;
    std::string name() const override;
};

#endif
