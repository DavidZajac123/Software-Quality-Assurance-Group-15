#include "Console.h"

#include <istream>
#include <ostream>

Console::Console(std::istream& input, std::ostream& output)
    : input_(input), output_(output) {
}

bool Console::readLine(std::string& line) {
    if (!std::getline(input_, line)) {
        return false;
    }

    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }

    return true;
}

bool Console::prompt(const std::string& question, std::string& answer) {
    showMessage(question);
    return readLine(answer);
}

void Console::showMessage(const std::string& message) {
    output_ << message << '\n';
}
