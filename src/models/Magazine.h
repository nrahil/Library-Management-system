#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "LibraryItem.h"

class Magazine : public LibraryItem {
public:
    Magazine(std::string title, std::string author, int catalogId, int issueNumber);

    std::string describe() const override;

private:
    int issueNumber_;
};

#endif
