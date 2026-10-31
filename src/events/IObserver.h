#ifndef IOBSERVER_H
#define IOBSERVER_H

#include "LibraryEvent.h"

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onEvent(const LibraryEvent& event) = 0;
};

#endif
