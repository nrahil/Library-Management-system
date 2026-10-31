#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
public:
    Student(int roll, std::string name, double balance);

    int getRoll() const;
    const std::string& getName() const;
    double getBalance() const;

    void deposit(double amount);
    void withdraw(double amount);

private:
    int roll_;
    std::string name_;
    double balance_;
};

#endif
