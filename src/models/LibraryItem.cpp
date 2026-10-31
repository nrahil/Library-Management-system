#include "LibraryItem.h"

LibraryItem::LibraryItem(std::string title, std::string author, int catalogId)
    : title_(std::move(title)), author_(std::move(author)), catalogId_(catalogId),
      state_(&AvailableState::instance()), issuedToRoll_(-1) {}

const std::string& LibraryItem::getTitle() const { return title_; }
const std::string& LibraryItem::getAuthor() const { return author_; }
int LibraryItem::getCatalogId() const { return catalogId_; }

void LibraryItem::setTitle(const std::string& title) { title_ = title; }
void LibraryItem::setAuthor(const std::string& author) { author_ = author; }

bool LibraryItem::isAvailable() const { return state_->canIssue(); }

void LibraryItem::issue() { state_->issue(*this); }
void LibraryItem::returnItem() { state_->returnItem(*this); }

void LibraryItem::setState(ItemState& state) { state_ = &state; }

int LibraryItem::issuedToRoll() const { return issuedToRoll_; }
void LibraryItem::setIssuedToRoll(int roll) { issuedToRoll_ = roll; }
