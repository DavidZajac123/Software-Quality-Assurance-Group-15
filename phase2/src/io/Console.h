#ifndef CONSOLE_H
#define CONSOLE_H

#include <iosfwd>
#include <string>

class Console {
public:
    Console(std::istream& input, std::ostream& output);

    bool readLine(std::string& line);

    bool prompt(const std::string& question, std::string& answer);

    void showMessage(const std::string& message);

private:
    std::istream& input_;
    std::ostream& output_;
};

#endif
