#include "FeePolicy.h"

double StandardFeePolicy::accountOpeningCost() const { return 20.0; }
double StandardFeePolicy::securityDeposit() const { return 30.0; }
double StandardFeePolicy::issueFee() const { return 2.0; }
double StandardFeePolicy::minimumInitialDeposit() const { return 50.0; }
