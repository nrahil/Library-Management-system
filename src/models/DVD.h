#ifndef DVD_H
#define DVD_H

#include "LibraryItem.h"

class DVD : public LibraryItem {
public:
    DVD(std::string title, std::string author, int catalogId, int runtimeMinutes);

    std::string describe() const override;

private:
    int runtimeMinutes_;
};

#endif
