"""One game-for-sale record."""
from __future__ import annotations

from dataclasses import dataclass


@dataclass
class GameListing:
    """One line of the available games file: the game name, the seller's username, and the price in whole cents."""

    game_name: str
    seller: str
    price_cents: int
