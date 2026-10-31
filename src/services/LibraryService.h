#ifndef LIBRARYSERVICE_H
#define LIBRARYSERVICE_H

#include <memory>
#include <string>
#include <vector>

#include "common/OperationResult.h"
#include "models/ItemFactory.h"
#include "models/LibraryItem.h"
#include "models/Student.h"
#include "policy/FeePolicy.h"
#include "repository/IItemRepository.h"
#include "repository/IRepository.h"
#include "services/CatalogService.h"
#include "services/CirculationService.h"
#include "services/ICatalogService.h"
#include "services/ICirculationService.h"
#include "services/IStudentService.h"
#include "services/StudentService.h"

// LibraryService acts as an overarching Facade that orchestrates the
// modular domain services (StudentService, CatalogService, CirculationService).
// Callers can either talk to this Facade or interact with the individual
// specialized services directly.
class LibraryService : public IStudentService, public ICatalogService, public ICirculationService {
public:
    // Modular constructor taking injected service instances
    LibraryService(IStudentService& studentService,
                   ICatalogService& catalogService,
                   ICirculationService& circulationService);

    // Convenience constructor wiring default services over repositories and fee policy
    LibraryService(IRepository<Student>& students,
                   IItemRepository& items,
                   const IFeePolicy& feePolicy);

    // Direct access to underlying modular services
    IStudentService& getStudentService() { return studentService_; }
    ICatalogService& getCatalogService() { return catalogService_; }
    ICirculationService& getCirculationService() { return circulationService_; }

    // IStudentService operations (delegates to studentService_)
    OperationResult createAccount(int roll, const std::string& name, double initialDeposit) override;
    Student* findStudent(int roll) override;
    OperationResult depositAmount(int roll, double amount) override;
    std::vector<Student> listStudentsSorted() override;
    void checkLowBalance(const Student& student) override;

    // ICatalogService operations (delegates to catalogService_)
    OperationResult addItem(ItemFactory::ItemType type, const std::string& title, const std::string& author,
                             int catalogId, int extraNumeric) override;
    OperationResult editItem(int catalogId, const std::string& newTitle, const std::string& newAuthor) override;
    LibraryItem* findItem(int catalogId) override;
    std::vector<LibraryItem*> listAllItems() override;
    std::vector<LibraryItem*> listAvailableItems() override;

    // ICirculationService operations (delegates to circulationService_)
    OperationResult issueItem(int roll, int catalogId) override;
    OperationResult returnItem(int roll, int catalogId) override;
    std::vector<LibraryItem*> listItemsHeldBy(int roll) override;

private:
    std::unique_ptr<StudentService> ownedStudentService_;
    std::unique_ptr<CatalogService> ownedCatalogService_;
    std::unique_ptr<CirculationService> ownedCirculationService_;

    IStudentService& studentService_;
    ICatalogService& catalogService_;
    ICirculationService& circulationService_;
};

#endif // LIBRARYSERVICE_H

