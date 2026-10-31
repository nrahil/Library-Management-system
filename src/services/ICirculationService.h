#ifndef ICIRCULATIONSERVICE_H
#define ICIRCULATIONSERVICE_H

#include <vector>

#include "common/OperationResult.h"
#include "models/LibraryItem.h"

class ICirculationService {
public:
    virtual ~ICirculationService() = default;

    virtual OperationResult issueItem(int roll, int catalogId) = 0;
    virtual OperationResult returnItem(int roll, int catalogId) = 0;
    virtual std::vector<LibraryItem*> listItemsHeldBy(int roll) = 0;
};

#endif // ICIRCULATIONSERVICE_H

