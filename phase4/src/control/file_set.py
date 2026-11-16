"""The seven file names one Back End run works with."""
from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True)
class FileSet:
    """Holds the names of the four input files and the three output files of one Back End run, in command-line order."""

    old_users: str
    old_games: str
    old_collection: str
    merged_transactions: str
    new_users: str
    new_games: str
    new_collection: str
