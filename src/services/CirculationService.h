#ifndef CIRCULATIONSERVICE_H
#define CIRCULATIONSERVICE_H

#include "policy/FeePolicy.h"
#include "services/ICatalogService.h"
#include "services/ICirculationService.h"
#include "services/IStudentService.h"

// Dedicated service for Book/Item Circulation (Issuing, Returning, Loans).
class CirculationService : public ICirculationService {
public:
    CirculationService(IStudentService& studentService,
                       ICatalogService& catalogService,
                       const IFeePolicy& feePolicy);

    OperationResult issueItem(int roll, int catalogId) override;
    OperationResult returnItem(int roll, int catalogId) override;
    std::vector<LibraryItem*> listItemsHeldBy(int roll) override;

private:
    IStudentService& studentService_;
    ICatalogService& catalogService_;
    const IFeePolicy& feePolicy_;
};

#endif // CIRCULATIONSERVICE_H

