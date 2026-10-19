#include "Transaction.h"

// Returns true by default because transactions normally require
// an active logged-in session.
bool Transaction::requiresLogin() const {
    return true;
}

bool Transaction::isPermittedFor(UserType type) const {
    (void)type;
    return true;
}