"""Reads the three old master files."""
from __future__ import annotations

from state.game_listing import GameListing
from state.owned_game import OwnedGame
from state.user_account import UserAccount

END_MARKER = "END"


class MasterFileReader:
    """Reads the three old master files into account, listing and owned-game records; a line that does not fit its layout, or a file with no END line, stops the batch with a FatalInputError."""

    def read_accounts(self, file_name: str) -> list[UserAccount]:
        """Reads the current user accounts file, one UserAccount per 28-character line: username(15) space type(2) space credit(9)."""
        raise NotImplementedError

    def read_listings(self, file_name: str) -> list[GameListing]:
        """Reads the available games file, one GameListing per 49-character line: game(26) space seller(15) space price(6)."""
        raise NotImplementedError

    def read_collection(self, file_name: str) -> list[OwnedGame]:
        """Reads the game collection file, one OwnedGame per 42-character line: game(26) space owner(15)."""
        raise NotImplementedError

    def _read_lines(self, file_name: str) -> list[str]:
        """Returns the lines before the END line without their line endings; raises FatalInputError when the file cannot be opened or has no END line."""
        raise NotImplementedError
