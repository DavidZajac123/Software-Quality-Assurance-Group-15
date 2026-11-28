"""Unit tests for utilities/fatal_input_error.py: FatalInputError."""

import pytest
from utilities.fatal_input_error import FatalInputError

class TestFatalInputErrorInit:
    """Statement coverage for FatalInputError.__init__."""

    def test_keeps_file_name_and_description(self):
        error = FatalInputError("users.txt", "missing END line")
        assert error.file_name == "users.txt"
        assert error.description == "missing END line"

    def test_message_is_description_then_file_name(self):
        error = FatalInputError("users.txt", "missing END line")
        assert str(error) == "missing END line (file: users.txt)"

    def test_can_be_raised_and_caught(self):
        with pytest.raises(FatalInputError, match="missing END line"):
            raise FatalInputError("users.txt", "missing END line")