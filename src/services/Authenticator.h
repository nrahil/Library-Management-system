#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <string>
#include "services/IAuthService.h"

// Password verification service. Implements IAuthService.
class Authenticator : public IAuthService {
public:
    Authenticator();
    explicit Authenticator(std::string correctPassword);

    bool validate(const std::string& password) const override;
    bool authenticate(const std::string& password) const override;

private:
    std::string correctPassword_;
};

// Alias for service naming convention
using AuthService = Authenticator;

#endif // AUTHENTICATOR_H
