#include "Money.h"

#include <cctype>
#include <iomanip>
#include <sstream>

// Parses a monetary text value into whole cents.
// Returns false for invalid or unsupported monetary input.
// A valid amount is one or more digits, optionally followed by a point and
// one or two digits (message catalogue rule 5): "5", "5.5" and "5.50" are
// valid; "", ".5", "5.", "-5", "+5", "5.505" and "5.5.0" are not.
// An amount too large to store is set to a value above every limit, so the
// range checks reject it instead of the arithmetic overflowing.
bool Money::parse(
    const std::string& text,
    long long& cents
) {
    const std::size_t pointPosition = text.find('.');

    std::string dollarsText = text.substr(0, pointPosition);
    std::string centsText;

    if (pointPosition != std::string::npos) {
        centsText = text.substr(pointPosition + 1);

        if (centsText.empty() || centsText.size() > 2) {
            return false;
        }
    }

    if (dollarsText.empty()) {
        return false;
    }

    for (char character : dollarsText + centsText) {
        if (!std::isdigit(static_cast<unsigned char>(character))) {
            return false;
        }
    }

    const std::size_t firstNonZero = dollarsText.find_first_not_of('0');
    dollarsText =
        firstNonZero == std::string::npos ? "0" : dollarsText.substr(firstNonZero);

    if (dollarsText.size() > MAX_DOLLAR_DIGITS) {
        cents = TOO_LARGE_CENTS;
        return true;
    }

    centsText.resize(2, '0');
    cents = std::stoll(dollarsText) * 100 + std::stoll(centsText);
    return true;
}

// Formats a whole-cent value as a zero-filled fixed-width monetary field.
std::string Money::toFileField(
    long long cents,
    std::size_t width
) {
    long long dollars = cents / 100;
    long long remainingCents = cents % 100;

    std::ostringstream amount;
    amount
        << dollars
        << '.'
        << std::setw(2)
        << std::setfill('0')
        << remainingCents;

    std::string result = amount.str();

    if (result.size() < width) {
        result = std::string(width - result.size(), '0') + result;
    }

    return result;
}

// Formats a whole-cent value for console display with two decimal places.
std::string Money::toDisplay(long long cents) {
    long long dollars = cents / 100;
    long long remainingCents = cents % 100;

    std::ostringstream amount;
    amount
        << dollars
        << '.'
        << std::setw(2)
        << std::setfill('0')
        << remainingCents;

    return amount.str();
}