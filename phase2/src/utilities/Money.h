#pragma once

#include <cstddef>
#include <string>

// Converts monetary text to and from whole cents.
// Money is stored as integers to avoid floating-point rounding errors.
class Money {
public:
    static bool parse(
        const std::string& text,
        long long& cents
    );

    static std::string toFileField(
        long long cents,
        std::size_t width
    );

    static std::string toDisplay(long long cents);
};