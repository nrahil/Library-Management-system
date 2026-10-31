#include "services/LibraryService.h"

LibraryService::LibraryService(IStudentService& studentService,
                               ICatalogService& catalogService,
                               ICirculationService& circulationService)
    : studentService_(studentService),
      catalogService_(catalogService),
      circulationService_(circulationService) {}

LibraryService::LibraryService(IRepository<Student>& students,
                               IItemRepository& items,
                               const IFeePolicy& feePolicy)
    : ownedStudentService_(std::make_unique<StudentService>(students, feePolicy)),
      ownedCatalogService_(std::make_unique<CatalogService>(items)),
      ownedCirculationService_(std::make_unique<CirculationService>(*ownedStudentService_, *ownedCatalogService_, feePolicy)),
      studentService_(*ownedStudentService_),
      catalogService_(*ownedCatalogService_),
      circulationService_(*ownedCirculationService_) {}

OperationResult LibraryService::createAccount(int roll, const std::string& name, double initialDeposit) {
    return studentService_.createAccount(roll, name, initialDeposit);
}

Student* LibraryService::findStudent(int roll) {
    return studentService_.findStudent(roll);
}

OperationResult LibraryService::depositAmount(int roll, double amount) {
    return studentService_.depositAmount(roll, amount);
}

std::vector<Student> LibraryService::listStudentsSorted() {
    return studentService_.listStudentsSorted();
}

void LibraryService::checkLowBalance(const Student& student) {
    studentService_.checkLowBalance(student);
}

OperationResult LibraryService::addItem(ItemFactory::ItemType type, const std::string& title,
                                         const std::string& author, int catalogId, int extraNumeric) {
    return catalogService_.addItem(type, title, author, catalogId, extraNumeric);
}

OperationResult LibraryService::editItem(int catalogId, const std::string& newTitle, const std::string& newAuthor) {
    return catalogService_.editItem(catalogId, newTitle, newAuthor);
}

LibraryItem* LibraryService::findItem(int catalogId) {
    return catalogService_.findItem(catalogId);
}

std::vector<LibraryItem*> LibraryService::listAllItems() {
    return catalogService_.listAllItems();
}

std::vector<LibraryItem*> LibraryService::listAvailableItems() {
    return catalogService_.listAvailableItems();
}

OperationResult LibraryService::issueItem(int roll, int catalogId) {
    return circulationService_.issueItem(roll, catalogId);
}

OperationResult LibraryService::returnItem(int roll, int catalogId) {
    return circulationService_.returnItem(roll, catalogId);
}

std::vector<LibraryItem*> LibraryService::listItemsHeldBy(int roll) {
    return circulationService_.listItemsHeldBy(roll);
}

