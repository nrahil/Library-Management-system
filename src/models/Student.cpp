#include "Student.h"

Student::Student(int roll, std::string name, double balance)
    : roll_(roll), name_(std::move(name)), balance_(balance) {}

int Student::getRoll() const { return roll_; }
const std::string& Student::getName() const { return name_; }
double Student::getBalance() const { return balance_; }

void Student::deposit(double amount) { balance_ += amount; }
void Student::withdraw(double amount) { balance_ -= amount; }
