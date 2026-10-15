#pragma once

// Represents the four account types used by the Front End.
// The two-letter file codes are converted separately by UserTypeCodes.
enum class UserType {
    Admin,
    FullStandard,
    BuyStandard,
    SellStandard
};
