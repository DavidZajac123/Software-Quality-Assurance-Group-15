#include "FixedWidthFormat.h"

// Pads text on the right with spaces until it reaches the requested width.
// Callers are expected to provide text that already fits the field width.
std::string FixedWidthFormat::padRight(
    const std::string& text,
    std::size_t width
) {
    if (text.size() >= width) {
        return text;
    }

    return text + std::string(width - text.size(), ' ');
}

// Extracts a fixed-width field from a line and removes trailing padding spaces.
std::string FixedWidthFormat::extractField(
    const std::string& line,
    std::size_t start,
    std::size_t width
) {
    if (start >= line.size()) {
        return "";
    }

    std::string field = line.substr(start, width);

    while (!field.empty() && field.back() == ' ') {
        field.pop_back();
    }

    return field;
}