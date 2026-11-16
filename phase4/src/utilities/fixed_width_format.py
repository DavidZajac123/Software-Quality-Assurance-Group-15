"""Fixed-width field widths, padding and slicing for the master files."""
from __future__ import annotations


class FixedWidthFormat:
    """The field widths of the three master files, and the padding and slicing every reader and writer uses, so no width or padding rule is written twice."""

    USERNAME_WIDTH = 15
    USER_TYPE_WIDTH = 2
    CREDIT_WIDTH = 9
    GAME_NAME_WIDTH = 26
    PRICE_WIDTH = 6

    @staticmethod
    def pad_right(text: str, width: int) -> str:
        """Returns text left-justified and filled with spaces to exactly width characters."""
        raise NotImplementedError

    @staticmethod
    def field(line: str, start: int, width: int) -> str:
        """Returns the width characters of line from position start with the trailing spaces removed; raises ValueError when line is too short."""
        raise NotImplementedError
