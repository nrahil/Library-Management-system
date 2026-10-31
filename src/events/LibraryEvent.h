#ifndef LIBRARYEVENT_H
#define LIBRARYEVENT_H

#include <string>

enum class EventType { ItemAdded, ItemIssued, ItemReturned, AccountCreated, LowBalance };

struct LibraryEvent {
    EventType type;
    std::string message;
};

#endif
