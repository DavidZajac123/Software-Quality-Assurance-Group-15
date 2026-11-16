"""Reads the merged daily transaction file."""
from __future__ import annotations

from transactions.add_credit_transaction import AddCreditTransaction
from transactions.buy_transaction import BuyTransaction
from transactions.create_transaction import CreateTransaction
from transactions.delete_transaction import DeleteTransaction
from transactions.end_of_session_transaction import EndOfSessionTransaction
from transactions.refund_transaction import RefundTransaction
from transactions.sell_transaction import SellTransaction
from transactions.transaction import Transaction


class TransactionFileReader:
    """Reads the merged daily transaction file and turns every record into the matching Transaction object. The field widths of the daily transaction file are class constants here and nowhere else, so adopting another group's Front End changes only this class."""

    CODE_WIDTH = 2
    USERNAME_WIDTH = 15
    USER_TYPE_WIDTH = 2
    CREDIT_WIDTH = 9
    GAME_NAME_WIDTH = 26
    PRICE_WIDTH = 6

    def read(self, file_name: str) -> list[Transaction]:
        """Returns one Transaction per line in file order; the final lone 00 line (the empty daily file) becomes an EndOfSessionTransaction like any other 00 record. Raises FatalInputError when the file cannot be opened."""
        raise NotImplementedError

    def _parse(self, line: str) -> Transaction:
        """Dispatches on the first two characters to the matching _parse method; an unknown code, or a line too short for its layout, raises FatalInputError."""
        raise NotImplementedError

    def _parse_create(self, line: str) -> CreateTransaction:
        """Parses 01 username(15) type(2) credit(9)."""
        raise NotImplementedError

    def _parse_delete(self, line: str) -> DeleteTransaction:
        """Parses 02 username(15) blank(2) credit(9)."""
        raise NotImplementedError

    def _parse_sell(self, line: str) -> SellTransaction:
        """Parses 03 game(26) seller(15) price(6)."""
        raise NotImplementedError

    def _parse_buy(self, line: str) -> BuyTransaction:
        """Parses 04 game(26) seller(15) buyer(15) price(6)."""
        raise NotImplementedError

    def _parse_refund(self, line: str) -> RefundTransaction:
        """Parses 05 buyer(15) seller(15) amount(9)."""
        raise NotImplementedError

    def _parse_add_credit(self, line: str) -> AddCreditTransaction:
        """Parses 06 username(15) blank(2) amount(9)."""
        raise NotImplementedError

    def _parse_end_of_session(self, line: str) -> EndOfSessionTransaction:
        """Parses 00, ignoring the rest of the line, so both the Front End's padded 00 record and a bare 00 line are accepted."""
        raise NotImplementedError
