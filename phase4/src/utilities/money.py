"""Money conversion between file text and whole cents."""
from __future__ import annotations


class Money:
    """Converts between the money text of the files (digits, a point and two decimals, zero-filled to the field width) and whole cents, so no arithmetic is ever done in floating point."""

    @staticmethod
    def parse(text: str) -> int:
        """Returns the number of cents in text such as "000020.00"; raises ValueError when text is not digits, a point and exactly two digits."""
        raise NotImplementedError

    @staticmethod
    def format(cents: int, width: int) -> str:
        """Returns cents as dollars and cents with two decimals, zero-filled on the left to exactly width characters; for example 2000 and 9 give "000020.00"."""
        raise NotImplementedError
