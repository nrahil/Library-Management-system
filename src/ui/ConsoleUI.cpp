#include "ui/ConsoleUI.h"

#include <iomanip>
#include <iostream>

#include "ui/Console.h"

using std::cin;
using std::cout;
using std::endl;
using console::Color;

ConsoleUI::ConsoleUI(IStudentService& studentService,
                     ICatalogService& catalogService,
                     ICirculationService& circulationService,
                     const Authenticator& authenticator)
    : studentService_(studentService),
      catalogService_(catalogService),
      circulationService_(circulationService),
      authenticator_(authenticator) {}

ConsoleUI::ConsoleUI(LibraryService& library, const Authenticator& authenticator)
    : studentService_(library.getStudentService()),
      catalogService_(library.getCatalogService()),
      circulationService_(library.getCirculationService()),
      authenticator_(authenticator) {}

void ConsoleUI::printResult(const OperationResult& result) {
    cout << console::colorize(result.message, result.success ? Color::Green : Color::Red) << "\n";
}

void ConsoleUI::run() {
    console::printHeader("LIBRARY MANAGEMENT SYSTEM");

    while (true) {
        console::printDivider();
        cout << "Login as:\n1. Admin\n2. Student\n0. Exit\n";
        int option;
        cin >> option;

        if (option == 0) {
            break;
        }

        bool isAdmin = (option == 1);

        cout << "Enter password: ";
        std::string password;
        cin >> password;

        if (!authenticator_.validate(password)) {
            cout << console::colorize("Incorrect password.", Color::Red) << "\n";
            continue;
        }

        if (isAdmin) {
            handleAdminMenu();
        } else {
            handleStudentMenu();
        }
    }

    cout << console::colorize("Goodbye!", Color::Cyan) << "\n";
}

void ConsoleUI::handleAdminMenu() {
    while (true) {
        console::printDivider();
        cout << console::colorize("ADMIN MENU", Color::Bold) << "\n";
        cout << "1. Add item\n2. Edit item\n3. View item status\n"
                "4. View enrolled students\n5. View student balance\n0. Logout\n";
        int option;
        cin >> option;

        if (option == 0) {
            return;
        }

        switch (option) {
            case 1: promptAddItem(); break;
            case 2: promptEditItem(); break;
            case 3: viewAllItems(); break;
            case 4: viewStudentsSorted(); break;
            case 5: {
                int roll;
                cout << "Enter student roll number: ";
                cin >> roll;
                promptDisplayStudent(roll);
                break;
            }
            default: break;
        }
    }
}

void ConsoleUI::handleStudentMenu() {
    int roll;
    cout << "Enter your roll number: ";
    cin >> roll;

    if (studentService_.findStudent(roll) == nullptr) {
        cout << "Student not found. Create an account? (1. Yes / 2. No): ";
        int option;
        cin >> option;
        if (option == 1) {
            promptCreateAccount();
        }
        return;
    }

    while (true) {
        console::printDivider();
        cout << console::colorize("STUDENT MENU", Color::Bold) << "\n";
        cout << "1. View balance\n2. Deposit amount\n3. Issue item\n"
                "4. Return item\n5. View issued items\n0. Logout\n";
        int option;
        cin >> option;

        if (option == 0) {
            return;
        }

        switch (option) {
            case 1: promptDisplayStudent(roll); break;
            case 2: promptDepositAmount(roll); break;
            case 3: promptIssueItem(roll); break;
            case 4: promptReturnItem(roll); break;
            case 5: viewIssuedItems(roll); break;
            default: break;
        }
    }
}

void ConsoleUI::promptCreateAccount() {
    int roll;
    cout << "Enter roll number (BBRRRR format): ";
    cin >> roll;

    cout << "Enter student name: ";
    cin.ignore();
    std::string name;
    std::getline(cin, name);

    double initialDeposit;
    cout << "Enter initial deposit amount ($50 minimum): ";
    cin >> initialDeposit;

    OperationResult result = studentService_.createAccount(roll, name, initialDeposit);
    printResult(result);
}

void ConsoleUI::promptDisplayStudent(int roll) {
    Student* student = studentService_.findStudent(roll);
    if (student == nullptr) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Roll No: " << student->getRoll() << endl;
    cout << "Name: " << student->getName() << endl;
    cout << "Balance: $" << std::fixed << std::setprecision(2) << student->getBalance() << endl;
}

void ConsoleUI::promptDepositAmount(int roll) {
    double amount;
    cout << "Enter the amount to deposit: ";
    cin >> amount;

    OperationResult result = studentService_.depositAmount(roll, amount);
    printResult(result);
}

void ConsoleUI::promptIssueItem(int roll) {
    std::vector<LibraryItem*> available = catalogService_.listAvailableItems();

    cout << "Available items:\n";
    for (size_t i = 0; i < available.size(); i++) {
        cout << i + 1 << ". " << available[i]->describe() << "\n";
    }

    int choice;
    cout << "Enter the number of the item you want to issue (0 to cancel): ";
    cin >> choice;

    if (choice == 0) {
        return;
    }

    if (choice < 1 || static_cast<size_t>(choice) > available.size()) {
        cout << "Cannot issue the item. Insufficient balance or item is unavailable.\n";
        return;
    }

    int catalogId = available[choice - 1]->getCatalogId();
    OperationResult result = circulationService_.issueItem(roll, catalogId);
    printResult(result);
}

void ConsoleUI::promptReturnItem(int roll) {
    std::vector<LibraryItem*> held = circulationService_.listItemsHeldBy(roll);

    if (held.empty()) {
        cout << "You have no items to return.\n";
        return;
    }

    cout << "Items you currently hold:\n";
    for (size_t i = 0; i < held.size(); i++) {
        cout << i + 1 << ". " << held[i]->describe() << "\n";
    }

    int choice;
    cout << "Enter the number of the item you want to return (0 to cancel): ";
    cin >> choice;

    if (choice == 0) {
        return;
    }

    if (choice < 1 || static_cast<size_t>(choice) > held.size()) {
        cout << "Invalid selection.\n";
        return;
    }

    int catalogId = held[choice - 1]->getCatalogId();
    OperationResult result = circulationService_.returnItem(roll, catalogId);
    printResult(result);
}

void ConsoleUI::viewIssuedItems(int roll) {
    std::vector<LibraryItem*> held = circulationService_.listItemsHeldBy(roll);

    if (held.empty()) {
        cout << "You have no issued items.\n";
        return;
    }

    cout << "Items currently issued to you:\n";
    for (LibraryItem* item : held) {
        cout << "- " << item->describe() << "\n";
    }
}

void ConsoleUI::promptAddItem() {
    cout << "Item type:\n1. Book\n2. DVD\n3. Magazine\n";
    int typeChoice;
    cin >> typeChoice;

    ItemFactory::ItemType type;
    switch (typeChoice) {
        case 2: type = ItemFactory::ItemType::Dvd; break;
        case 3: type = ItemFactory::ItemType::Magazine; break;
        default: type = ItemFactory::ItemType::Book; break;
    }

    cout << "Enter title: ";
    cin.ignore();
    std::string title;
    std::getline(cin, title);

    cout << "Enter author: ";
    std::string author;
    std::getline(cin, author);

    int catalogId;
    cout << "Enter catalog ID (ISBN for books): ";
    cin >> catalogId;

    int extraNumeric = 0;
    if (type == ItemFactory::ItemType::Dvd) {
        cout << "Enter runtime in minutes: ";
        cin >> extraNumeric;
    } else if (type == ItemFactory::ItemType::Magazine) {
        cout << "Enter issue number: ";
        cin >> extraNumeric;
    }

    OperationResult result = catalogService_.addItem(type, title, author, catalogId, extraNumeric);
    printResult(result);
}

void ConsoleUI::promptEditItem() {
    int catalogId;
    cout << "Enter catalog ID to edit: ";
    cin >> catalogId;

    LibraryItem* item = catalogService_.findItem(catalogId);
    if (item == nullptr) {
        cout << "Item not found.\n";
        return;
    }

    cout << "Current title: " << item->getTitle() << endl;
    cout << "Enter new title: ";
    cin.ignore();
    std::string newTitle;
    std::getline(cin, newTitle);

    cout << "Current author: " << item->getAuthor() << endl;
    cout << "Enter new author: ";
    std::string newAuthor;
    std::getline(cin, newAuthor);

    OperationResult result = catalogService_.editItem(catalogId, newTitle, newAuthor);
    printResult(result);
}

void ConsoleUI::viewAllItems() {
    for (LibraryItem* item : catalogService_.listAllItems()) {
        std::string status = item->isAvailable() ? "Available" : "Issued";
        cout << item->describe() << " - "
             << console::colorize(status, item->isAvailable() ? Color::Green : Color::Yellow) << "\n";
    }
}

void ConsoleUI::viewStudentsSorted() {
    for (const Student& student : studentService_.listStudentsSorted()) {
        cout << student.getRoll() << " - " << student.getName() << " - Balance: $"
             << std::fixed << std::setprecision(2) << student.getBalance() << endl;
    }
}

