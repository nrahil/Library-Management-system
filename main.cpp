#include "events/ConsoleAuditObserver.h"
#include "events/NotificationCenter.h"
#include "models/ItemFactory.h"
#include "models/Student.h"
#include "policy/FeePolicy.h"
#include "repository/InMemoryItemRepository.h"
#include "repository/InMemoryRepository.h"
#include "services/Authenticator.h"
#include "services/CatalogService.h"
#include "services/CirculationService.h"
#include "services/LibraryService.h"
#include "services/StudentService.h"
#include "ui/ConsoleUI.h"

#ifdef _WIN32
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

// Legacy cmd.exe doesn't interpret ANSI color codes unless this flag is
// set; Windows Terminal/PowerShell already default to it, but set it
// unconditionally so colored output works either way.
void enableAnsiOnWindows() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(handle, &mode)) {
        SetConsoleMode(handle, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
}
#endif

int main() {
#ifdef _WIN32
    enableAnsiOnWindows();
#endif

    // 1. Repositories and Policy Configuration
    InMemoryRepository<Student> studentRepository;
    InMemoryItemRepository itemRepository;
    StandardFeePolicy feePolicy;
    Authenticator authenticator;

    // 2. Notification & Audit setup
    ConsoleAuditObserver auditObserver;
    NotificationCenter::instance().subscribe(&auditObserver);

    // Seed initial 15 placeholder books
    for (int i = 0; i < 15; i++) {
        itemRepository.add(ItemFactory::create(ItemFactory::ItemType::Book, "Title", "Author", i + 1000, 0));
    }

    // 3. Initialize Modular Domain Services
    StudentService studentService(studentRepository, feePolicy);
    CatalogService catalogService(itemRepository);
    CirculationService circulationService(studentService, catalogService, feePolicy);

    // 4. Initialize UI with modular services
    ConsoleUI ui(studentService, catalogService, circulationService, authenticator);
    ui.run();

    return 0;
}
