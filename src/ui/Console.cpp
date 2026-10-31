#include "Console.h"

#include <iostream>

namespace console {

namespace {
const char* codeFor(Color color) {
    switch (color) {
        case Color::Green: return "\033[32m";
        case Color::Red: return "\033[31m";
        case Color::Yellow: return "\033[33m";
        case Color::Cyan: return "\033[36m";
        case Color::Bold: return "\033[1m";
        default: return "";
    }
}
} // namespace

std::string colorize(const std::string& text, Color color) {
    if (color == Color::Default) {
        return text;
    }
    return std::string(codeFor(color)) + text + "\033[0m";
}

void printHeader(const std::string& title) {
    std::string border(title.size() + 8, '=');
    std::cout << colorize(border, Color::Cyan) << "\n";
    std::cout << colorize("    " + title + "    ", Color::Bold) << "\n";
    std::cout << colorize(border, Color::Cyan) << "\n";
}

void printDivider() {
    std::cout << colorize(std::string(40, '-'), Color::Cyan) << "\n";
}

} // namespace console
