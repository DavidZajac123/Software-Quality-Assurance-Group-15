"""All the data of the system while a batch runs."""
from __future__ import annotations

from state.game_listing import GameListing
from state.owned_game import OwnedGame
from state.user_account import UserAccount


class SystemState:
    """Everything the Back End knows while a batch runs: all accounts, games for sale and owned games, changed only through these methods so that every rule lives in one place."""

    def __init__(self, accounts: list[UserAccount], listings: list[GameListing], collection: list[OwnedGame]) -> None:
        """Takes ownership of the three lists read from the old master files."""
        self._accounts = accounts
        self._listings = listings
        self._collection = collection

    def accounts(self) -> list[UserAccount]:
        """Returns the accounts in file order, for the writer."""
        return self._accounts

    def listings(self) -> list[GameListing]:
        """Returns the games for sale in file order, for the writer."""
        return self._listings

    def collection(self) -> list[OwnedGame]:
        """Returns the owned games in file order, for the writer."""
        return self._collection

    def find_account(self, username: str) -> UserAccount | None:
        """Returns the account with this username, or None when there is none."""
        raise NotImplementedError

    def add_account(self, account: UserAccount) -> None:
        """Appends a new account; the caller has already checked that the username is unused."""
        raise NotImplementedError

    def remove_account(self, username: str) -> None:
        """Removes the account, every game it sells and every game it owns (Phase 2 decision D25)."""
        raise NotImplementedError

    def change_credit(self, username: str, delta_cents: int) -> None:
        """Adds delta_cents (negative to subtract) to the account's credit; the caller has already checked that the balance cannot go negative."""
        raise NotImplementedError

    def find_listing(self, game_name: str) -> GameListing | None:
        """Returns the game for sale with this name, or None when there is none."""
        raise NotImplementedError

    def add_listing(self, listing: GameListing) -> None:
        """Appends a new game for sale; the caller has already checked that the name is unused."""
        raise NotImplementedError

    def owns_game(self, username: str, game_name: str) -> bool:
        """Returns True when this user already has this game in their collection."""
        raise NotImplementedError

    def add_owned_game(self, owned_game: OwnedGame) -> None:
        """Appends a game to the collection; the caller has already checked that the user does not own it."""
        raise NotImplementedError
