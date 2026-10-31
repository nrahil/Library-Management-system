#ifndef IAUTHSERVICE_H
#define IAUTHSERVICE_H

#include <string>

class IAuthService {
public:
    virtual ~IAuthService() = default;
    virtual bool validate(const std::string& password) const = 0;
    virtual bool authenticate(const std::string& password) const {
        return validate(password);
    }
};

#endif // IAUTHSERVICE_H
