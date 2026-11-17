"""Fixed-width field widths, padding and slicing for the master files."""
from __future__ import annotations


class FixedWidthFormat:
    """The field widths of the three master files, and the padding and slicing every reader and writer uses, so no width or padding rule is written twice."""

    USERNAME_WIDTH = 15
    USER_TYPE_WIDTH = 2
    CREDIT_WIDTH = 9
    GAME_NAME_WIDTH = 26
    PRICE_WIDTH = 6

    # Whole-line widths of the three master files (fields joined by single spaces).
    ACCOUNT_LINE_WIDTH = USERNAME_WIDTH + 1 + USER_TYPE_WIDTH + 1 + CREDIT_WIDTH        # 28
    LISTING_LINE_WIDTH = GAME_NAME_WIDTH + 1 + USERNAME_WIDTH + 1 + PRICE_WIDTH         # 49
    COLLECTION_LINE_WIDTH = GAME_NAME_WIDTH + 1 + USERNAME_WIDTH                        # 42

    @staticmethod
    def pad_right(text: str, width: int) -> str:
        """Returns text left-justified and filled with spaces to exactly width characters; raises ValueError when text is longer than width."""
        if len(text) > width:
            raise ValueError(f"{text!r} is longer than {width} characters")
        return text.ljust(width, " ")

    @staticmethod
    def field(line: str, start: int, width: int) -> str:
        """Returns the width characters of line from position start with the trailing spaces removed; raises ValueError when line is too short."""
        if start < 0 or width < 0:
            raise ValueError(f"invalid field position: start {start}, width {width}")
        end = start + width
        if end > len(line):
            raise ValueError(f"line is {len(line)} characters, too short for a field ending at position {end}")
        return line[start:end].rstrip(" ")
