"""Shared fixtures for the Phase 5 Back End unit tests.

Only two fixtures live here. Everything else a test needs is written inside the test itself,
so each test can be read on its own.
"""
import pytest

from state.game_listing import GameListing
from state.owned_game import OwnedGame
from state.system_state import SystemState
from state.user_account import UserAccount
from state.user_type import UserType


@pytest.fixture
def write_text(tmp_path):
    """Returns a function write_text(name, text) that writes text to a file in this test's own
    temporary folder exactly as given, with no line-ending translation, and returns the file's
    path as a string (the readers take file names as strings).

    Use "\\n" or "\\r\\n" in text to choose the line endings. A test that needs bytes that are not
    valid UTF-8 should write them itself with (tmp_path / name).write_bytes(...)."""
    def write(name, text):
        path = tmp_path / name
        # newline="" turns off translation, so "\n" stays LF and "\r\n" stays CRLF on every platform.
        with open(path, "w", encoding="utf-8", newline="") as file:
            file.write(text)
        return str(path)
    return write


@pytest.fixture
def make_state():
    """Returns a function make_state() that builds a new SystemState every time it is called,
    with new lists and new record objects, so no test can see another test's changes.

    The contents match the old master files in phase4/sample_data:
        accounts:   AdminUser AA 1000.00, FullUser FS 100.00, Seller1 SS 50.00, Buyer1 BS 20.00
        listings:   Minecraft by Seller1 at 50.00, Terraria by FullUser at 10.00
        collection: Terraria owned by Buyer1"""
    def make():
        return SystemState(
            [
                UserAccount("AdminUser", UserType.ADMIN, 100000),
                UserAccount("FullUser", UserType.FULL_STANDARD, 10000),
                UserAccount("Seller1", UserType.SELL_STANDARD, 5000),
                UserAccount("Buyer1", UserType.BUY_STANDARD, 2000),
            ],
            [
                GameListing("Minecraft", "Seller1", 5000),
                GameListing("Terraria", "FullUser", 1000),
            ],
            [
                OwnedGame("Terraria", "Buyer1"),
            ],
        )
    return make
