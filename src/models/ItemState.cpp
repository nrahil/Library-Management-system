#include "ItemState.h"

#include "LibraryItem.h"

ItemState& AvailableState::instance() {
    static AvailableState instance;
    return instance;
}

bool AvailableState::canIssue() const { return true; }
bool AvailableState::canReturn() const { return false; }

void AvailableState::issue(LibraryItem& item) const {
    item.setState(IssuedState::instance());
}

void AvailableState::returnItem(LibraryItem&) const {
    // Already available; nothing to do. Caller (LibraryService) checks
    // canReturn() first and reports a friendly message instead of relying
    // on this no-op.
}

std::string AvailableState::name() const { return "Available"; }

ItemState& IssuedState::instance() {
    static IssuedState instance;
    return instance;
}

bool IssuedState::canIssue() const { return false; }
bool IssuedState::canReturn() const { return true; }

void IssuedState::issue(LibraryItem&) const {
    // Already issued; nothing to do. Caller checks canIssue() first.
}

void IssuedState::returnItem(LibraryItem& item) const {
    item.setState(AvailableState::instance());
}

std::string IssuedState::name() const { return "Issued"; }
