#include "services/CirculationService.h"

#include <string>

#include "common/FormatUtils.h"
#include "events/NotificationCenter.h"

CirculationService::CirculationService(IStudentService& studentService,
                                       ICatalogService& catalogService,
                                       const IFeePolicy& feePolicy)
    : studentService_(studentService), catalogService_(catalogService), feePolicy_(feePolicy) {}

OperationResult CirculationService::issueItem(int roll, int catalogId) {
    Student* student = studentService_.findStudent(roll);
    if (student == nullptr) {
        return {false, "Student not found."};
    }

    LibraryItem* item = catalogService_.findItem(catalogId);
    if (item == nullptr || !item->isAvailable()) {
        return {false, "Cannot issue the item. Item is unavailable."};
    }

    if (student->getBalance() < feePolicy_.issueFee()) {
        return {false, "Cannot issue the item. Insufficient balance."};
    }

    item->issue();
    item->setIssuedToRoll(roll);
    student->withdraw(feePolicy_.issueFee());

    NotificationCenter::instance().publish(
        {EventType::ItemIssued, "Item issued to roll " + std::to_string(roll) + ": " + item->describe()});
    studentService_.checkLowBalance(*student);

    return {true, "Item issued successfully. New balance: $" + FormatUtils::formatMoney(student->getBalance())};
}

OperationResult CirculationService::returnItem(int roll, int catalogId) {
    LibraryItem* item = catalogService_.findItem(catalogId);
    if (item == nullptr || item->isAvailable() || item->issuedToRoll() != roll) {
        return {false, "Cannot return this item. It is not currently issued to you."};
    }

    item->returnItem();
    item->setIssuedToRoll(-1);

    NotificationCenter::instance().publish(
        {EventType::ItemReturned, "Item returned by roll " + std::to_string(roll) + ": " + item->describe()});

    return {true, "Item returned successfully."};
}

std::vector<LibraryItem*> CirculationService::listItemsHeldBy(int roll) {
    std::vector<LibraryItem*> held;
    for (LibraryItem* item : catalogService_.listAllItems()) {
        if (item->issuedToRoll() == roll) {
            held.push_back(item);
        }
    }
    return held;
}

