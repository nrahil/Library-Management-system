#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

// Presentation-only helpers (ANSI colors, boxed headers). Kept separate
// from ConsoleUI's menu logic so styling changes never touch business
// flow -- same SRP reasoning as the rest of the UI layer.
namespace console {

enum class Color { Default, Green, Red, Yellow, Cyan, Bold };

std::string colorize(const std::string& text, Color color);
void printHeader(const std::string& title);
void printDivider();

} // namespace console

#endif
