"""Writes the three new master files."""
from __future__ import annotations

import os

from state.game_listing import GameListing
from state.owned_game import OwnedGame
from state.user_account import UserAccount
from utilities.fixed_width_format import FixedWidthFormat as Fmt
from utilities.money import Money

END_MARKER = "END"


class MasterFileWriter:
    """Writes the three new master files in their fixed-width layouts, each ending with an END line; creates the output folder when it does not exist."""

    def write_accounts(self, file_name: str, accounts: list[UserAccount]) -> None:
        """Writes one 28-character line per account: username(15) space type(2) space credit(9)."""
        lines = [
            " ".join((
                Fmt.pad_right(account.username, Fmt.USERNAME_WIDTH),
                Fmt.pad_right(account.user_type.code, Fmt.USER_TYPE_WIDTH),
                Money.format(account.credit_cents, Fmt.CREDIT_WIDTH),
            ))
            for account in accounts
        ]
        self._write_lines(file_name, lines)

    def write_listings(self, file_name: str, listings: list[GameListing]) -> None:
        """Writes one 49-character line per game for sale: game(26) space seller(15) space price(6)."""
        lines = [
            " ".join((
                Fmt.pad_right(listing.game_name, Fmt.GAME_NAME_WIDTH),
                Fmt.pad_right(listing.seller, Fmt.USERNAME_WIDTH),
                Money.format(listing.price_cents, Fmt.PRICE_WIDTH),
            ))
            for listing in listings
        ]
        self._write_lines(file_name, lines)

    def write_collection(self, file_name: str, collection: list[OwnedGame]) -> None:
        """Writes one 42-character line per owned game: game(26) space owner(15)."""
        lines = [
            " ".join((
                Fmt.pad_right(owned_game.game_name, Fmt.GAME_NAME_WIDTH),
                Fmt.pad_right(owned_game.owner, Fmt.USERNAME_WIDTH),
            ))
            for owned_game in collection
        ]
        self._write_lines(file_name, lines)

    def _write_lines(self, file_name: str, lines: list[str]) -> None:
        """Creates the folder if needed, then writes the lines followed by the END line, one per line."""
        # Every line is built before the file is opened, so a value that does not fit its field
        # (ValueError from pad_right or Money.format) stops the write before this file is touched.
        folder = os.path.dirname(file_name)
        if folder:
            os.makedirs(folder, exist_ok=True)
        # newline="\n" writes LF on every platform, including Windows.
        with open(file_name, "w", encoding="utf-8", newline="\n") as file:
            for line in lines:
                file.write(line + "\n")
            file.write(END_MARKER + "\n")
