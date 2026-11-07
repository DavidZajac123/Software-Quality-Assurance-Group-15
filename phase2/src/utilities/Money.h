#pragma once

#include <cstddef>
#include <string>

// Converts monetary text to and from whole cents.
// Money is stored as integers to avoid floating-point rounding errors.
class Money {
public:
    // Amounts with more whole-dollar digits than this are too large to store
    // and are set to TOO_LARGE_CENTS, which is above every limit.
    static constexpr std::size_t MAX_DOLLAR_DIGITS = 12;
    static constexpr long long TOO_LARGE_CENTS = 100000000000000LL;

    // Converts monetary text such as "15.50" into whole cents.
    // Returns false when the text is not a valid amount.
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