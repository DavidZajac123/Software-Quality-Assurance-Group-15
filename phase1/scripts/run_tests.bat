@echo off
REM Runs run_tests.sh with Git Bash and passes on its exit status.
setlocal
set "BASH_EXE=%ProgramFiles%\Git\bin\bash.exe"
if not exist "%BASH_EXE%" set "BASH_EXE=bash"
"%BASH_EXE%" "%~dp0run_tests.sh" %*
exit /b %ERRORLEVEL%
