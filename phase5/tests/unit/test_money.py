"""Unit tests for utilities/money.py: Money.parse and Money.format."""
import pytest

from utilities.money import Money


# ---------- Money.parse ----------

def test_parse_normal_value_returns_cents():
    assert Money.parse("000020.00") == 2000


def test_parse_value_with_cents_only():
    assert Money.parse("000000.01") == 1


def test_parse_zero_is_lower_boundary():
    assert Money.parse("000000.00") == 0


def test_parse_maximum_credit_value():
    assert Money.parse("999999.99") == 99999999


def test_parse_does_not_check_field_width():
    # Width is checked by the readers' layout checks, not by parse.
    assert Money.parse("20.00") == 2000


@pytest.mark.parametrize("text", [
    "20.0",          # only one digit after the point
    "000020",        # no decimal point
    "000020.00 ",    # space padding
    "-00020.00",     # minus sign
    "",              # empty field
    "\u0660\u0660\u0660\u0660\u0662\u0660.\u0660\u0660",  # Arabic-Indic digits: \d would accept them, [0-9] does not
])
def test_parse_malformed_value_raises_value_error(text):
    with pytest.raises(ValueError, match="invalid money value"):
        Money.parse(text)


# ---------- Money.format ----------

def test_format_zero():
    assert Money.format(0, 9) == "000000.00"


def test_format_normal_value_is_zero_filled():
    assert Money.format(2000, 9) == "000020.00"


def test_format_single_digit_cents_keep_two_decimals():
    assert Money.format(5, 9) == "000000.05"


def test_format_price_field_width_6():
    assert Money.format(5000, 6) == "050.00"


def test_format_maximum_value_that_fits_width_9():
    assert Money.format(99999999, 9) == "999999.99"


def test_format_negative_value_raises_value_error():
    with pytest.raises(ValueError, match="negative money value"):
        Money.format(-1, 9)


def test_format_value_too_large_for_width_raises_value_error():
    # 1000000.00 needs 10 characters; this is the limit behind known limitation L3.
    with pytest.raises(ValueError, match="does not fit in 9 characters"):
        Money.format(100000000, 9)
