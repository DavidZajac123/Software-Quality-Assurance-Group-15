#include "Transaction.h"

bool Transaction::requiresLogin() const {
    return true;
}

bool Transaction::isPermittedFor(UserType type) const {
    (void)type;
    return true;
}