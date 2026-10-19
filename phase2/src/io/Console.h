#ifndef CONSOLE_H
#define CONSOLE_H

#include <iosfwd>
#include <string>

// Handles all Front End console input and output.
class Console {
public:
    // Connects the console to the provided input and output streams.
    Console(std::istream& input, std::ostream& output);

    // Reads one line of input, removes a trailing carriage return,
    // and returns false when the input stream ends.
    bool readLine(std::string& line);

    // Displays a prompt and reads the user's response.
    bool prompt(const std::string& question, std::string& answer);

    // Displays one message followed by a newline.
    void showMessage(const std::string& message);

private:
    std::istream& input_;
    std::ostream& output_;
};

#endif