"""Writes the three new master files."""
from __future__ import annotations

from state.game_listing import GameListing
from state.owned_game import OwnedGame
from state.user_account import UserAccount

END_MARKER = "END"


class MasterFileWriter:
    """Writes the three new master files in their fixed-width layouts, each ending with an END line; creates the output folder when it does not exist."""

    def write_accounts(self, file_name: str, accounts: list[UserAccount]) -> None:
        """Writes one 28-character line per account: username(15) space type(2) space credit(9)."""
        raise NotImplementedError

    def write_listings(self, file_name: str, listings: list[GameListing]) -> None:
        """Writes one 49-character line per game for sale: game(26) space seller(15) space price(6)."""
        raise NotImplementedError

    def write_collection(self, file_name: str, collection: list[OwnedGame]) -> None:
        """Writes one 42-character line per owned game: game(26) space owner(15)."""
        raise NotImplementedError

    def _write_lines(self, file_name: str, lines: list[str]) -> None:
        """Creates the folder if needed, then writes the lines followed by the END line, one per line."""
        raise NotImplementedError
