#include "services/StudentService.h"

#include <algorithm>

#include "common/FormatUtils.h"
#include "events/NotificationCenter.h"

StudentService::StudentService(IRepository<Student>& students, const IFeePolicy& feePolicy)
    : students_(students), feePolicy_(feePolicy) {}

Student* StudentService::findStudent(int roll) {
    return students_.find([roll](const Student& s) { return s.getRoll() == roll; });
}

void StudentService::checkLowBalance(const Student& student) {
    if (student.getBalance() < LOW_BALANCE_THRESHOLD) {
        NotificationCenter::instance().publish(
            {EventType::LowBalance, "Low balance warning: student " + std::to_string(student.getRoll()) +
                                         " balance is $" + FormatUtils::formatMoney(student.getBalance())});
    }
}

OperationResult StudentService::createAccount(int roll, const std::string& name, double initialDeposit) {
    if (findStudent(roll) != nullptr) {
        return {false, "Account already exists for this roll number."};
    }

    if (initialDeposit < feePolicy_.minimumInitialDeposit()) {
        return {false, "Initial deposit must be at least $" + FormatUtils::formatMoney(feePolicy_.minimumInitialDeposit()) + "."};
    }

    double openingBalance = initialDeposit - feePolicy_.accountOpeningCost() - feePolicy_.securityDeposit();
    students_.add(Student(roll, name, openingBalance));

    NotificationCenter::instance().publish(
        {EventType::AccountCreated, "Account created for roll " + std::to_string(roll) + " (" + name + ")."});

    return {true, "Account created."};
}

OperationResult StudentService::depositAmount(int roll, double amount) {
    Student* student = findStudent(roll);
    if (student == nullptr) {
        return {false, "Student not found."};
    }

    student->deposit(amount);
    return {true, "New balance: $" + FormatUtils::formatMoney(student->getBalance())};
}

std::vector<Student> StudentService::listStudentsSorted() {
    std::vector<Student> sorted(students_.all().begin(), students_.all().end());
    std::sort(sorted.begin(), sorted.end(), [](const Student& a, const Student& b) {
        return a.getRoll() < b.getRoll();
    });
    return sorted;
}

