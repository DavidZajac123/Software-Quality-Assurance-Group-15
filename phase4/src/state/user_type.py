"""The kinds of user account."""
from __future__ import annotations

from enum import Enum


class UserType(Enum):
    """The five kinds of account, each with the two-letter code written in the files. ACCOUNT_MANAGER (AM) was added by the client on 10 November 2026; the Back End only stores the type, the Front End enforces what each type may do."""

    ADMIN = "AA"
    FULL_STANDARD = "FS"
    BUY_STANDARD = "BS"
    SELL_STANDARD = "SS"
    ACCOUNT_MANAGER = "AM"

    @property
    def code(self) -> str:
        """Returns the two-letter code written in the files, for example "AA"."""
        return self.value

    @classmethod
    def from_code(cls, code: str) -> UserType:
        """Returns the UserType for a two-letter code; raises ValueError naming the code when it is not one of the five."""
        try:
            return cls(code)
        except ValueError:
            raise ValueError(f"unknown account type code {code!r}") from None
