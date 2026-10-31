#include "ConsoleAuditObserver.h"

#include <iostream>

#include "ui/Console.h"

void ConsoleAuditObserver::onEvent(const LibraryEvent& event) {
    std::cout << console::colorize("[NOTICE] " + event.message, console::Color::Yellow) << "\n";
}
