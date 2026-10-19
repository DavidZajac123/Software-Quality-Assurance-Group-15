Phase 2 AI Usage

Generative AI (ChatGPT) was used during Phase 2 of the CSCI 3060U Software Quality Assurance project.

AI was used to assist with:

- reviewing and interpreting the Phase 2 Front End Rapid Prototype requirements;
- reviewing the group’s preliminary and updated system design and UML structure;
- identifying the effect of the Week 4 privileged transaction on the design;
- suggesting a read-only account collection accessor for the Session design;
- identifying which parts of the implementation were stable enough to begin before the UML was finalized;
- drafting the initial session-state data types UserType, UserAccount, GameListing, and OwnedGame;
- drafting the FixedWidthFormat, Money, and UserTypeCodes utility classes based on the finalized UML;
- interpreting fixed-width field offsets, END-record handling, user-type codes, and monetary values stored as whole cents;
- diagnosing C++/VS Code IntelliSense issues and distinguishing environment problems from code errors;
- configuring and verifying the C++ compiler environment using Visual Studio C++ tooling and the Windows SDK;
- identifying and correcting the FixedWidthFormat::padRight truncation mismatch;
- adding fixed-record-length validation to MasterFileReader for the three master-file formats;
- improving class and method comments to match the Phase 2 internal-documentation requirements;
- implementing the InputRules utility class and its shared validation constants and methods;
- implementing the Transaction class and its shared validation constants and methods;
- implemented the abstract Transaction base class according to the finalized UML and shared transaction interface.
- implementing the Session class and its account, credit, listing, ownership, and per-session state-management methods according to the finalized UML;
- implementing ListGamesTransaction using the finalized transaction design and the team's Console interface;
- implementing LogoutTransaction using the team's completed DailyTransactionWriter, Console, and Session interfaces;
- implementing CreateTransaction with admin permission checking, username/account-type validation, Session account creation, and 01 DTF recording according to the finalized design;
- implementing DeleteTransaction with admin permission checking, account-existence/current-user validation, Session account removal, and 02 DTF recording according to the finalized design;
- implementing AddCreditTransaction with monetary validation, administrator target-account handling, per-session credit limits, maximum-balance checking, Session updates, and 06 DTF recording according to the finalized design;
- implementing SellTransaction with account-type permission checking, game-name and price validation, session game-name reservation, and 03 DTF recording according to the finalized design;
- implementing BuyTransaction with account-type permission checking, listing/seller validation, self-purchase and ownership checks, credit transfer, collection updates, and 04 DTF recording according to the finalized design;
- implementing RefundTransaction with admin permission checking, buyer/seller account validation, refund amount validation, credit transfer, and 05 DTF recording according to the finalized design;
- implementing LoginTransaction with fresh master-file loading, username validation, pre-login transaction handling, and Session initialization according to the finalized design;
- implementing the client-added ListAccountsTransaction and Session::accounts() accessor according to the updated near-final design, including admin-only access and active-account display with no DTF record;
- auditing the Phase 2 implementation against the updated near-final design and making small alignment fixes to FixedWidthFormat::padRight(), AddCreditTransaction validation order, and ListGamesTransaction empty-list behavior;

AI-assisted code and design suggestions were reviewed against the Phase 2 requirements, the group’s finalized system design, the project requirements, and the available client/TA updates before being incorporated into the project.

The file prompt_response_history.txt contains a reconstructed record of the main relevant AI-assisted interactions associated with the work submitted for Phase 2.