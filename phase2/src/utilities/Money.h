#pragma once

#include <cstddef>
#include <string>

// Converts monetary text to and from whole cents.
// Money is stored as integers to avoid floating-point rounding errors.
class Money {
public:
    // Converts monetary text such as "15.50" into whole cents.
    static bool parse(
        const std::string& text,
        long long& cents
    );

    // Formats whole cents as a zero-filled fixed-width monetary field.
    static std::string toFileField(
        long long cents,
        std::size_t width
    );

    // Formats whole cents for display with two decimal places.
    static std::string toDisplay(long long cents);
};