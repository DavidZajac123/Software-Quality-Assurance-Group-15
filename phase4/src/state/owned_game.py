"""One owned-game record."""
from __future__ import annotations

from dataclasses import dataclass


@dataclass
class OwnedGame:
    """One line of the game collection file: the game name and the owner's username."""

    game_name: str
    owner: str
