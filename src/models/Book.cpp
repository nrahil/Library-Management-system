#include "Book.h"

Book::Book(std::string title, std::string author, int isbn)
    : LibraryItem(std::move(title), std::move(author), isbn) {}

std::string Book::describe() const {
    return "Book: " + getTitle() + " by " + getAuthor() + " (ISBN: " + std::to_string(getCatalogId()) + ")";
}
