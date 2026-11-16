"""The exception that stops a batch on bad input."""
from __future__ import annotations


class FatalInputError(Exception):
    """Raised by a reader when an input file is malformed; carries the file name and a description so the Back End can stop and log a fatal error."""

    def __init__(self, file_name: str, description: str) -> None:
        """Keeps the file name and the description, and builds the exception message from them."""
        super().__init__(f"{description} (file: {file_name})")
        self.file_name = file_name
        self.description = description
