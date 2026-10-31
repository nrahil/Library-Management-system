#ifndef NOTIFICATIONCENTER_H
#define NOTIFICATIONCENTER_H

#include <vector>

#include "IObserver.h"

// Singleton + Observer Subject: one global event bus. LibraryService
// publishes here directly (NotificationCenter::instance()), which is a
// deliberate use of global access -- it trades a bit of testability for
// the textbook Singleton, the same tradeoff real interviews probe on.
class NotificationCenter {
public:
    static NotificationCenter& instance();

    void subscribe(IObserver* observer);
    void publish(const LibraryEvent& event) const;

    NotificationCenter(const NotificationCenter&) = delete;
    NotificationCenter& operator=(const NotificationCenter&) = delete;

private:
    NotificationCenter() = default;

    std::vector<IObserver*> observers_;
};

#endif
