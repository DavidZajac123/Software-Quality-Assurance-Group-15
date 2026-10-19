#include "FixedWidthFormat.h"

std::string FixedWidthFormat::padRight(
    const std::string& text,
    std::size_t width
) {
    if (text.size() >= width) {
        return text;
    }

    return text + std::string(width - text.size(), ' ');
}

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