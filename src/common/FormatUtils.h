#ifndef FORMATUTILS_H
#define FORMATUTILS_H

#include <iomanip>
#include <sstream>
#include <string>

namespace FormatUtils {
inline std::string formatMoney(double amount) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << amount;
    return out.str();
}
} // namespace FormatUtils

#endif // FORMATUTILS_H

