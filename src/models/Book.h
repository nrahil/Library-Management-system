#ifndef BOOK_H
#define BOOK_H

#include "LibraryItem.h"

class Book : public LibraryItem {
public:
    Book(std::string title, std::string author, int isbn);

    std::string describe() const override;
};

#endif
