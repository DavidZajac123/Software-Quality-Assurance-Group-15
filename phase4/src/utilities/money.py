"""Money conversion between file text and whole cents."""
from __future__ import annotations

import re

# Digits, a point and exactly two digits; [0-9] rather than \d so that non-ASCII digits are rejected.
_MONEY_PATTERN = re.compile(r"([0-9]+)\.([0-9]{2})")


class Money:
    """Converts between the money text of the files (digits, a point and two decimals, zero-filled to the field width) and whole cents, so no arithmetic is ever done in floating point."""

    @staticmethod
    def parse(text: str) -> int:
        """Returns the number of cents in text such as "000020.00"; raises ValueError when text is not digits, a point and exactly two digits."""
        match = _MONEY_PATTERN.fullmatch(text)
        if match is None:
            raise ValueError(f"invalid money value {text!r}")
        dollars, cents = match.groups()
        return int(dollars) * 100 + int(cents)

    @staticmethod
    def format(cents: int, width: int) -> str:
        """Returns cents as dollars and cents with two decimals, zero-filled on the left to exactly width characters; for example 2000 and 9 give "000020.00". Raises ValueError when cents is negative or the amount does not fit in width characters."""
        if cents < 0:
            raise ValueError(f"negative money value {cents} cents")
        text = f"{cents // 100}.{cents % 100:02d}".rjust(width, "0")
        if len(text) > width:
            raise ValueError(f"money value {cents} cents does not fit in {width} characters")
        return text
