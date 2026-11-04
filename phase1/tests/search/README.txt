Search Requirements Tests

Tests for search, added by the client's change request: show every game for sale and every user whose
name contains the search text; non-admins do not see admins who are not selling games.

Number of test cases: 9

These tests cover each account type, games only, users only, both, the admin-visibility rule (search_06
uses a fixture with an admin who is selling), blank text, refusal before login, and case-sensitive matching.

Expected wording: phase3/message_catalogue.md. search writes no Daily Transaction File record.
