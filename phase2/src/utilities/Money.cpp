#include "Money.h"

#include <cctype>
#include <iomanip>
#include <sstream>

bool Money::parse(
    const std::string& text,
    long long& cents
) {
    if (text.empty()) {
        return false;
    }

    std::size_t decimalPosition = text.find('.');

    if (
        decimalPosition != std::string::npos &&
        text.find('.', decimalPosition + 1) != std::string::npos
    ) {
        return false;
    }

    std::string dollarsText;
    std::string centsText;

    if (decimalPosition == std::string::npos) {
        dollarsText = text;
        centsText = "00";
    } else {
        dollarsText = text.substr(0, decimalPosition);
        centsText = text.substr(decimalPosition + 1);

        if (centsText.size() == 1) {
            centsText += '0';
        }

        if (centsText.size() != 2) {
            return false;
        }
    }

    if (dollarsText.empty()) {
        dollarsText = "0";
    }

    for (char character : dollarsText) {
        if (!std::isdigit(static_cast<unsigned char>(character))) {
            return false;
        }
    }

    for (char character : centsText) {
        if (!std::isdigit(static_cast<unsigned char>(character))) {
            return false;
        }
    }

    try {
        long long dollars = std::stoll(dollarsText);
        long long remainingCents = std::stoll(centsText);

        cents = dollars * 100 + remainingCents;
    } catch (...) {
        return false;
    }

    return true;
}

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