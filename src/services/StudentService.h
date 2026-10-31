#ifndef STUDENTSERVICE_H
#define STUDENTSERVICE_H

#include "policy/FeePolicy.h"
#include "repository/IRepository.h"
#include "services/IStudentService.h"

// Dedicated service for Student and Account management.
class StudentService : public IStudentService {
public:
    StudentService(IRepository<Student>& students, const IFeePolicy& feePolicy);

    OperationResult createAccount(int roll, const std::string& name, double initialDeposit) override;
    Student* findStudent(int roll) override;
    OperationResult depositAmount(int roll, double amount) override;
    std::vector<Student> listStudentsSorted() override;
    void checkLowBalance(const Student& student) override;

private:
    static constexpr double LOW_BALANCE_THRESHOLD = 5.0;

    IRepository<Student>& students_;
    const IFeePolicy& feePolicy_;
};

#endif // STUDENTSERVICE_H

