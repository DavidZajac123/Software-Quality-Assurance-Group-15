"""Unit tests for utilities/error_log.py: ErrorLog."""

from utilities.error_log import ErrorLog

RECORD = "04 Minecraft Seller1 Buyer1 050.00"  # any text; ErrorLog prints it unchanged


class TestErrorLogInit:
    """Statement coverage for ErrorLog.__init__."""

    def test_new_log_has_no_errors(self):
        assert ErrorLog().count() == 0


class TestErrorLogFailedConstraint:
    """Statement coverage for ErrorLog.failed_constraint (README decision B2)."""

    def test_prints_failed_constraint_line(self, capsys):
        ErrorLog().failed_constraint("Buyer 'Buyer1' has insufficient credit.", RECORD)
        assert capsys.readouterr().out == (
            "ERROR: Failed constraint: Buyer 'Buyer1' has insufficient credit. "
            f"(transaction: {RECORD})\n")

    def test_counts_the_error(self):
        log = ErrorLog()
        log.failed_constraint("any reason", RECORD)
        assert log.count() == 1


class TestErrorLogFatal:
    """Statement coverage for ErrorLog.fatal (README decision B4)."""

    def test_prints_fatal_line(self, capsys):
        ErrorLog().fatal("missing END line", "users.txt")
        assert capsys.readouterr().out == "ERROR: Fatal input error: missing END line (file: users.txt)\n"

    def test_counts_the_error(self):
        log = ErrorLog()
        log.fatal("missing END line", "users.txt")
        assert log.count() == 1


class TestErrorLogCount:
    """Statement coverage for ErrorLog.count."""

    def test_counts_every_kind_of_error(self):
        log = ErrorLog()
        log.failed_constraint("first", RECORD)
        log.failed_constraint("second", RECORD)
        log.fatal("third", "users.txt")
        assert log.count() == 3