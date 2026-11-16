"""One account record."""
from __future__ import annotations

from dataclasses import dataclass

from state.user_type import UserType


@dataclass
class UserAccount:
    """One line of the current user accounts file: the username, its account type, and its credit in whole cents."""

    username: str
    user_type: UserType
    credit_cents: int
