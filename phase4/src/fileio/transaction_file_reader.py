"""Reads the merged daily transaction file."""
from __future__ import annotations

from state.user_type import UserType
from transactions.add_credit_transaction import AddCreditTransaction
from transactions.buy_transaction import BuyTransaction
from transactions.create_transaction import CreateTransaction
from transactions.delete_transaction import DeleteTransaction
from transactions.end_of_session_transaction import EndOfSessionTransaction
from transactions.refund_transaction import RefundTransaction
from transactions.sell_transaction import SellTransaction
from transactions.transaction import Transaction
from utilities.fatal_input_error import FatalInputError
from utilities.fixed_width_format import FixedWidthFormat
from utilities.money import Money


class TransactionFileReader:
    """Reads the merged daily transaction file and turns every record into the matching Transaction object. The field widths of the daily transaction file are class constants here and nowhere else, so adopting another group's Front End changes only this class."""

    CODE_WIDTH = 2
    USERNAME_WIDTH = 15
    USER_TYPE_WIDTH = 2
    CREDIT_WIDTH = 9
    GAME_NAME_WIDTH = 26
    PRICE_WIDTH = 6

    # Field start positions; the code and every field except the last are followed by one separator space.
    _FIELDS_START = CODE_WIDTH + 1                                   # 3
    # 01, 02, 06: code username type credit
    _USER_TYPE_START = _FIELDS_START + USERNAME_WIDTH + 1            # 19
    _USER_CREDIT_START = _USER_TYPE_START + USER_TYPE_WIDTH + 1      # 22
    _USER_RECORD_WIDTH = _USER_CREDIT_START + CREDIT_WIDTH           # 31
    # 03: code game seller price
    _SELL_SELLER_START = _FIELDS_START + GAME_NAME_WIDTH + 1         # 30
    _SELL_PRICE_START = _SELL_SELLER_START + USERNAME_WIDTH + 1      # 46
    _SELL_RECORD_WIDTH = _SELL_PRICE_START + PRICE_WIDTH             # 52
    # 04: code game seller buyer price
    _BUY_SELLER_START = _SELL_SELLER_START                           # 30
    _BUY_BUYER_START = _BUY_SELLER_START + USERNAME_WIDTH + 1         # 46
    _BUY_PRICE_START = _BUY_BUYER_START + USERNAME_WIDTH + 1         # 62
    _BUY_RECORD_WIDTH = _BUY_PRICE_START + PRICE_WIDTH               # 68
    # 05: code buyer seller amount
    _REFUND_SELLER_START = _FIELDS_START + USERNAME_WIDTH + 1        # 19
    _REFUND_AMOUNT_START = _REFUND_SELLER_START + USERNAME_WIDTH + 1  # 35
    _REFUND_RECORD_WIDTH = _REFUND_AMOUNT_START + CREDIT_WIDTH       # 44

    def read(self, file_name: str) -> list[Transaction]:
        """Returns one Transaction per line in file order; the final lone 00 line (the empty daily file) becomes an EndOfSessionTransaction like any other 00 record. Raises FatalInputError when the file cannot be opened, a line does not fit its layout, or the last transaction is not a 00 record."""
        try:
            # newline="" keeps the line endings as they are, so only "\n" or "\r\n" is removed below.
            with open(file_name, encoding="utf-8", newline="") as file:
                text = file.read()
        except OSError as error:
            raise FatalInputError(file_name, f"cannot be read ({error.strerror})") from None
        except UnicodeDecodeError:
            raise FatalInputError(file_name, "is not a text file") from None

        lines = text.split("\n")
        if lines[-1] == "":
            lines.pop()   # the empty piece after the final line ending is not a record
        transactions = []
        for number, line in enumerate(lines, start=1):
            if line.endswith("\r"):
                line = line[:-1]
            try:
                transactions.append(self._parse(line))
            except ValueError as error:
                raise FatalInputError(file_name, f"line {number}: {error}") from None

        if not transactions or transactions[-1].code() != EndOfSessionTransaction.CODE:
            raise FatalInputError(file_name, "does not end with a 00 transaction (the empty daily transaction file)")
        return transactions

    def _parse(self, line: str) -> Transaction:
        """Dispatches on the first two characters to the matching _parse method; an unknown code, or a line that does not fit its layout, raises ValueError, which read() reports as a FatalInputError naming the file and line."""
        code = line[:self.CODE_WIDTH]
        parsers = {
            EndOfSessionTransaction.CODE: self._parse_end_of_session,
            CreateTransaction.CODE: self._parse_create,
            DeleteTransaction.CODE: self._parse_delete,
            SellTransaction.CODE: self._parse_sell,
            BuyTransaction.CODE: self._parse_buy,
            RefundTransaction.CODE: self._parse_refund,
            AddCreditTransaction.CODE: self._parse_add_credit,
        }
        parser = parsers.get(code)
        if parser is None:
            raise ValueError(f"unknown transaction code {code!r}")
        return parser(line)

    def _parse_create(self, line: str) -> CreateTransaction:
        """Parses 01 username(15) type(2) credit(9)."""
        self._check_layout(line, self._USER_RECORD_WIDTH, (self._USER_TYPE_START - 1, self._USER_CREDIT_START - 1))
        return CreateTransaction(
            line,
            self._text(line, self._FIELDS_START, self.USERNAME_WIDTH),
            UserType.from_code(self._text(line, self._USER_TYPE_START, self.USER_TYPE_WIDTH)),
        )

    def _parse_delete(self, line: str) -> DeleteTransaction:
        """Parses 02 username(15) type(2) credit(9); only the username is used (decision B11)."""
        self._check_layout(line, self._USER_RECORD_WIDTH, (self._USER_TYPE_START - 1, self._USER_CREDIT_START - 1))
        return DeleteTransaction(line, self._text(line, self._FIELDS_START, self.USERNAME_WIDTH))

    def _parse_sell(self, line: str) -> SellTransaction:
        """Parses 03 game(26) seller(15) price(6)."""
        self._check_layout(line, self._SELL_RECORD_WIDTH, (self._SELL_SELLER_START - 1, self._SELL_PRICE_START - 1))
        return SellTransaction(
            line,
            self._text(line, self._FIELDS_START, self.GAME_NAME_WIDTH),
            self._text(line, self._SELL_SELLER_START, self.USERNAME_WIDTH),
            self._money(line, self._SELL_PRICE_START, self.PRICE_WIDTH),
        )

    def _parse_buy(self, line: str) -> BuyTransaction:
        """Parses 04 game(26) seller(15) buyer(15) price(6)."""
        self._check_layout(line, self._BUY_RECORD_WIDTH,
                           (self._BUY_SELLER_START - 1, self._BUY_BUYER_START - 1, self._BUY_PRICE_START - 1))
        return BuyTransaction(
            line,
            self._text(line, self._FIELDS_START, self.GAME_NAME_WIDTH),
            self._text(line, self._BUY_SELLER_START, self.USERNAME_WIDTH),
            self._text(line, self._BUY_BUYER_START, self.USERNAME_WIDTH),
            self._money(line, self._BUY_PRICE_START, self.PRICE_WIDTH),
        )

    def _parse_refund(self, line: str) -> RefundTransaction:
        """Parses 05 buyer(15) seller(15) amount(9)."""
        self._check_layout(line, self._REFUND_RECORD_WIDTH, (self._REFUND_SELLER_START - 1, self._REFUND_AMOUNT_START - 1))
        return RefundTransaction(
            line,
            self._text(line, self._FIELDS_START, self.USERNAME_WIDTH),
            self._text(line, self._REFUND_SELLER_START, self.USERNAME_WIDTH),
            self._money(line, self._REFUND_AMOUNT_START, self.CREDIT_WIDTH),
        )

    def _parse_add_credit(self, line: str) -> AddCreditTransaction:
        """Parses 06 username(15) type(2) credit(9); the username and the credit (the amount added, decision B9) are used, the type is not (decision B11)."""
        self._check_layout(line, self._USER_RECORD_WIDTH, (self._USER_TYPE_START - 1, self._USER_CREDIT_START - 1))
        return AddCreditTransaction(
            line,
            self._text(line, self._FIELDS_START, self.USERNAME_WIDTH),
            self._money(line, self._USER_CREDIT_START, self.CREDIT_WIDTH),
        )

    def _parse_end_of_session(self, line: str) -> EndOfSessionTransaction:
        """Parses 00 as either a bare 00 line or the 31-character layout 00 username(15) type(2) credit(9); in the long form only the layout is checked, and the field values are ignored (decision B11)."""
        if line != EndOfSessionTransaction.CODE:
            self._check_layout(line, self._USER_RECORD_WIDTH, (self._USER_TYPE_START - 1, self._USER_CREDIT_START - 1))
        return EndOfSessionTransaction(line)

    @staticmethod
    def _check_layout(line: str, width: int, separators: tuple[int, ...]) -> None:
        """Raises ValueError unless line is exactly width characters with a space after the code and at every separator position."""
        if len(line) != width:
            raise ValueError(f"{line[:2]} record is {len(line)} characters, expected {width}")
        for position in (TransactionFileReader.CODE_WIDTH,) + separators:
            if line[position] != " ":
                raise ValueError(f"{line[:2]} record has {line[position]!r} in column {position + 1}, expected a separator space")

    @staticmethod
    def _text(line: str, start: int, width: int) -> str:
        """Returns a space-padded text field with its trailing padding removed."""
        return FixedWidthFormat.field(line, start, width)

    @staticmethod
    def _money(line: str, start: int, width: int) -> int:
        """Returns a zero-filled money field in cents; it is sliced without stripping so that space padding is rejected."""
        return Money.parse(line[start:start + width])
