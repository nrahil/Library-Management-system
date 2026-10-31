#include "DVD.h"

DVD::DVD(std::string title, std::string author, int catalogId, int runtimeMinutes)
    : LibraryItem(std::move(title), std::move(author), catalogId), runtimeMinutes_(runtimeMinutes) {}

std::string DVD::describe() const {
    return "DVD: " + getTitle() + " by " + getAuthor() + " (ID: " + std::to_string(getCatalogId()) +
           ", " + std::to_string(runtimeMinutes_) + " min)";
}
