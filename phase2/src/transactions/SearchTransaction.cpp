#include "SearchTransaction.h"

#include <set>
#include <vector>

#include "ListGamesTransaction.h"
#include "../io/Console.h"
#include "../session/Session.h"

// Returns the command word that selects the search transaction.
std::string SearchTransaction::code() const {
    return "search";
}

// Returns true when the text is empty or contains only spaces and tabs.
bool SearchTransaction::isBlank(const std::string& text) {
    return text.find_first_not_of(" \t") == std::string::npos;
}

// Prompts for the search text and rejects blank text. Then prints the
// games for sale whose name contains the text, in name order, and the
// usernames that contain the text, in username order. Matching is
// case-sensitive. A non-admin is not shown an admin account that has
// no game for sale; an admin is shown every match.
void SearchTransaction::execute(
    Session& session,
    Console& console,
    DailyTransactionWriter& dtfWriter
) {
    (void)dtfWriter;

    std::string text;

    if (!console.prompt("Enter search text:", text)) {
        return;
    }

    if (isBlank(text)) {
        console.showMessage("Error: search text cannot be blank.");
        return;
    }

    const auto listings = session.listings();

    std::vector<std::string> gameLines;
    std::set<std::string> sellers;

    for (const auto& entry : listings) {
        sellers.insert(entry.second.sellerUsername);

        if (entry.first.find(text) != std::string::npos) {
            gameLines.push_back(
                ListGamesTransaction::formatListing(entry.second)
            );
        }
    }

    if (gameLines.empty()) {
        console.showMessage("No games match \"" + text + "\".");
    } else {
        console.showMessage("Games matching \"" + text + "\":");

        for (const std::string& line : gameLines) {
            console.showMessage(line);
        }
    }

    const bool viewerIsAdmin =
        session.currentUser().type == UserType::Admin;

    std::vector<std::string> usernames;

    for (const auto& entry : session.accounts()) {
        const UserAccount& account = entry.second;

        if (account.username.find(text) == std::string::npos) {
            continue;
        }

        const bool hiddenAdmin =
            account.type == UserType::Admin &&
            sellers.find(account.username) == sellers.end();

        if (hiddenAdmin && !viewerIsAdmin) {
            continue;
        }

        usernames.push_back(account.username);
    }

    if (usernames.empty()) {
        console.showMessage("No users match \"" + text + "\".");
        return;
    }

    console.showMessage("Users matching \"" + text + "\":");

    for (const std::string& username : usernames) {
        console.showMessage(username);
    }
}
