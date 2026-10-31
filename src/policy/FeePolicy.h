#ifndef FEEPOLICY_H
#define FEEPOLICY_H

// Strategy: pricing rules the library charges. LibraryService asks this
// interface for numbers instead of hardcoding them, so pricing can change
// (or vary per plan) by swapping implementations, not editing LibraryService.
class IFeePolicy {
public:
    virtual ~IFeePolicy() = default;

    virtual double accountOpeningCost() const = 0;
    virtual double securityDeposit() const = 0;
    virtual double issueFee() const = 0;
    virtual double minimumInitialDeposit() const = 0;
};

class StandardFeePolicy : public IFeePolicy {
public:
    double accountOpeningCost() const override;
    double securityDeposit() const override;
    double issueFee() const override;
    double minimumInitialDeposit() const override;
};

#endif
