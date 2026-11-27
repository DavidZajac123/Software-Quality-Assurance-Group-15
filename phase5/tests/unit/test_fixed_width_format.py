"""Unit tests for utilities/fixed_width_format.py: FixedWidthFormat.pad_right and FixedWidthFormat.field."""
import pytest

from utilities.fixed_width_format import FixedWidthFormat

# One 28-character line of the current user accounts file.
ACCOUNT_LINE = "AdminUser       AA 001000.00"


# ---------- FixedWidthFormat.pad_right ----------

def test_pad_right_shorter_text_is_filled_with_spaces():
    assert FixedWidthFormat.pad_right("Buyer1", 15) == "Buyer1         "


def test_pad_right_text_of_exact_width_is_unchanged():
    assert FixedWidthFormat.pad_right("ABCDEFGHIJKLMNO", 15) == "ABCDEFGHIJKLMNO"


def test_pad_right_text_longer_than_width_raises_value_error():
    with pytest.raises(ValueError, match="is longer than 15 characters"):
        FixedWidthFormat.pad_right("ABCDEFGHIJKLMNOP", 15)


# ---------- FixedWidthFormat.field ----------

def test_field_normal_extraction():
    assert FixedWidthFormat.field(ACCOUNT_LINE, 16, 2) == "AA"


def test_field_trailing_spaces_are_removed():
    assert FixedWidthFormat.field(ACCOUNT_LINE, 0, 15) == "AdminUser"


def test_field_leading_spaces_are_preserved():
    assert FixedWidthFormat.field("  ab  ", 0, 6) == "  ab"


def test_field_ending_exactly_at_line_end():
    assert FixedWidthFormat.field(ACCOUNT_LINE, 19, 9) == "001000.00"


def test_field_negative_start_raises_value_error():
    with pytest.raises(ValueError, match="invalid field position"):
        FixedWidthFormat.field(ACCOUNT_LINE, -1, 2)


def test_field_negative_width_raises_value_error():
    with pytest.raises(ValueError, match="invalid field position"):
        FixedWidthFormat.field(ACCOUNT_LINE, 0, -1)


def test_field_line_too_short_raises_value_error():
    # The field would end at position 29, one past the end of the 28-character line.
    with pytest.raises(ValueError, match="too short"):
        FixedWidthFormat.field(ACCOUNT_LINE, 20, 9)
