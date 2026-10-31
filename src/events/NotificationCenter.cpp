#include "NotificationCenter.h"

NotificationCenter& NotificationCenter::instance() {
    static NotificationCenter instance;
    return instance;
}

void NotificationCenter::subscribe(IObserver* observer) {
    observers_.push_back(observer);
}

void NotificationCenter::publish(const LibraryEvent& event) const {
    for (IObserver* observer : observers_) {
        observer->onEvent(event);
    }
}
