"""The abstract transaction that every record of the merged daily transaction file becomes."""
from __future__ import annotations

from abc import ABC, abstractmethod

from state.system_state import SystemState


class Transaction(ABC):
    """One record of the merged daily transaction file: knows its two-digit code, checks the business constraints against the system state, and applies its change to the state."""

    def __init__(self, record: str) -> None:
        """Keeps the record line exactly as it was read, for the error log."""
        self._record = record

    @property
    def record(self) -> str:
        """The record line exactly as it appeared in the merged daily transaction file."""
        return self._record

    @abstractmethod
    def code(self) -> str:
        """Returns the two-digit transaction code this class handles."""

    @abstractmethod
    def validate(self, state: SystemState) -> str:
        """Checks every constraint of this transaction against the state; returns a description of the first failed constraint, or an empty string when the transaction may be applied."""

    @abstractmethod
    def apply(self, state: SystemState) -> None:
        """Changes the state as the transaction requires; called only after validate returned an empty string."""
