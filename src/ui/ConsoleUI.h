#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "common/OperationResult.h"
#include "services/Authenticator.h"
#include "services/ICatalogService.h"
#include "services/ICirculationService.h"
#include "services/IStudentService.h"
#include "services/LibraryService.h"

// All cin/cout and menu flow lives here.
// Interacts with modular services: StudentService, CatalogService, CirculationService, and Authenticator.
class ConsoleUI {
public:
    // Modular constructor accepting decoupled domain services
    ConsoleUI(IStudentService& studentService,
              ICatalogService& catalogService,
              ICirculationService& circulationService,
              const Authenticator& authenticator);

    // Convenience constructor accepting the unified LibraryService facade
    ConsoleUI(LibraryService& library, const Authenticator& authenticator);

    void run();

private:
    void handleAdminMenu();
    void handleStudentMenu();

    void promptCreateAccount();
    void promptDisplayStudent(int roll);
    void promptDepositAmount(int roll);
    void promptIssueItem(int roll);
    void promptReturnItem(int roll);
    void viewIssuedItems(int roll);
    void promptAddItem();
    void promptEditItem();
    void viewAllItems();
    void viewStudentsSorted();
    void printResult(const OperationResult& result);

    IStudentService& studentService_;
    ICatalogService& catalogService_;
    ICirculationService& circulationService_;
    const Authenticator& authenticator_;
};

#endif // CONSOLEUI_H

