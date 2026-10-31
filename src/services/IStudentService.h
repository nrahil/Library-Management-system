#ifndef ISTUDENTSERVICE_H
#define ISTUDENTSERVICE_H

#include <string>
#include <vector>

#include "common/OperationResult.h"
#include "models/Student.h"

class IStudentService {
public:
    virtual ~IStudentService() = default;

    virtual OperationResult createAccount(int roll, const std::string& name, double initialDeposit) = 0;
    virtual Student* findStudent(int roll) = 0;
    virtual OperationResult depositAmount(int roll, double amount) = 0;
    virtual std::vector<Student> listStudentsSorted() = 0;
    virtual void checkLowBalance(const Student& student) = 0;
};

#endif // ISTUDENTSERVICE_H

