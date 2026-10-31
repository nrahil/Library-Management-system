#include "services/Authenticator.h"

Authenticator::Authenticator() : correctPassword_("password") {}

Authenticator::Authenticator(std::string correctPassword) : correctPassword_(std::move(correctPassword)) {}

bool Authenticator::validate(const std::string& password) const {
    return password == correctPassword_;
}

bool Authenticator::authenticate(const std::string& password) const {
    return validate(password);
}
