#pragma once

#include <cstddef>
#include <string>

// Provides the field widths and basic fixed-width string operations
// used by the master files and transaction files.
class FixedWidthFormat {
public:
    static constexpr std::size_t USERNAME_WIDTH = 15;
    static constexpr std::size_t TYPE_WIDTH = 2;
    static constexpr std::size_t CREDIT_WIDTH = 9;
    static constexpr std::size_t GAME_NAME_WIDTH = 26;
    static constexpr std::size_t PRICE_WIDTH = 6;

    // Pads text on the right with spaces until it reaches width.
    // Callers are expected to pass text that already fits the field width.
    static std::string padRight(
        const std::string& text,
        std::size_t width
    );

    // Extracts a fixed-width field and removes trailing padding spaces.
    static std::string extractField(
        const std::string& line,
        std::size_t start,
        std::size_t width
    );
};