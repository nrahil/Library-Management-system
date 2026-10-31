#include "Magazine.h"

Magazine::Magazine(std::string title, std::string author, int catalogId, int issueNumber)
    : LibraryItem(std::move(title), std::move(author), catalogId), issueNumber_(issueNumber) {}

std::string Magazine::describe() const {
    return "Magazine: " + getTitle() + " by " + getAuthor() + " (ID: " + std::to_string(getCatalogId()) +
           ", Issue #" + std::to_string(issueNumber_) + ")";
}
