#ifndef CONSOLEAUDITOBSERVER_H
#define CONSOLEAUDITOBSERVER_H

#include "IObserver.h"

class ConsoleAuditObserver : public IObserver {
public:
    void onEvent(const LibraryEvent& event) override;
};

#endif
