"""Reads the three old master files."""
from __future__ import annotations

from state.game_listing import GameListing
from state.owned_game import OwnedGame
from state.user_account import UserAccount
from state.user_type import UserType
from utilities.fatal_input_error import FatalInputError
from utilities.fixed_width_format import FixedWidthFormat as Fmt
from utilities.money import Money

END_MARKER = "END"

# Field start positions; every field is followed by one separator space except the last.
_TYPE_START = Fmt.USERNAME_WIDTH + 1                         # 16
_CREDIT_START = _TYPE_START + Fmt.USER_TYPE_WIDTH + 1        # 19
_SELLER_START = Fmt.GAME_NAME_WIDTH + 1                      # 27
_PRICE_START = _SELLER_START + Fmt.USERNAME_WIDTH + 1        # 43
_OWNER_START = Fmt.GAME_NAME_WIDTH + 1                       # 27


class MasterFileReader:
    """Reads the three old master files into account, listing and owned-game records; a line that does not fit its layout, or a file with no END line, stops the batch with a FatalInputError."""

    def read_accounts(self, file_name: str) -> list[UserAccount]:
        """Reads the current user accounts file, one UserAccount per 28-character line: username(15) space type(2) space credit(9)."""
        accounts = []
        for number, line in enumerate(self._read_lines(file_name), start=1):
            try:
                self._check_layout(line, "account", Fmt.ACCOUNT_LINE_WIDTH, (_TYPE_START - 1, _CREDIT_START - 1))
                accounts.append(UserAccount(
                    Fmt.field(line, 0, Fmt.USERNAME_WIDTH),
                    UserType.from_code(Fmt.field(line, _TYPE_START, Fmt.USER_TYPE_WIDTH)),
                    # Money fields are zero-filled, not space-padded, so they are sliced without stripping.
                    Money.parse(line[_CREDIT_START:_CREDIT_START + Fmt.CREDIT_WIDTH]),
                ))
            except ValueError as error:
                raise FatalInputError(file_name, f"line {number}: {error}") from None
        return accounts

    def read_listings(self, file_name: str) -> list[GameListing]:
        """Reads the available games file, one GameListing per 49-character line: game(26) space seller(15) space price(6)."""
        listings = []
        for number, line in enumerate(self._read_lines(file_name), start=1):
            try:
                self._check_layout(line, "game", Fmt.LISTING_LINE_WIDTH, (_SELLER_START - 1, _PRICE_START - 1))
                listings.append(GameListing(
                    Fmt.field(line, 0, Fmt.GAME_NAME_WIDTH),
                    Fmt.field(line, _SELLER_START, Fmt.USERNAME_WIDTH),
                    Money.parse(line[_PRICE_START:_PRICE_START + Fmt.PRICE_WIDTH]),
                ))
            except ValueError as error:
                raise FatalInputError(file_name, f"line {number}: {error}") from None
        return listings

    def read_collection(self, file_name: str) -> list[OwnedGame]:
        """Reads the game collection file, one OwnedGame per 42-character line: game(26) space owner(15)."""
        collection = []
        for number, line in enumerate(self._read_lines(file_name), start=1):
            try:
                self._check_layout(line, "collection", Fmt.COLLECTION_LINE_WIDTH, (_OWNER_START - 1,))
                collection.append(OwnedGame(
                    Fmt.field(line, 0, Fmt.GAME_NAME_WIDTH),
                    Fmt.field(line, _OWNER_START, Fmt.USERNAME_WIDTH),
                ))
            except ValueError as error:
                raise FatalInputError(file_name, f"line {number}: {error}") from None
        return collection

    def _read_lines(self, file_name: str) -> list[str]:
        """Returns the lines before the END line without their line endings; raises FatalInputError when the file cannot be opened or has no END line."""
        try:
            # newline="" keeps the line endings as they are, so only "\n" or "\r\n" is removed below.
            with open(file_name, encoding="utf-8", newline="") as file:
                text = file.read()
        except OSError as error:
            raise FatalInputError(file_name, f"cannot be read ({error.strerror})") from None
        except UnicodeDecodeError:
            raise FatalInputError(file_name, "is not a text file") from None

        lines = []
        for line in text.split("\n"):
            if line.endswith("\r"):
                line = line[:-1]
            if line.rstrip(" ") == END_MARKER:
                return lines
            lines.append(line)
        raise FatalInputError(file_name, "has no END line")

    @staticmethod
    def _check_layout(line: str, record_kind: str, width: int, separators: tuple[int, ...]) -> None:
        """Raises ValueError unless line is exactly width characters with a space at every separator position."""
        if len(line) != width:
            raise ValueError(f"{record_kind} record is {len(line)} characters, expected {width}")
        for position in separators:
            if line[position] != " ":
                raise ValueError(f"{record_kind} record has {line[position]!r} in column {position + 1}, expected a separator space")
