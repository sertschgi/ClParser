#ifndef CLPARSER_CLERRORS_HPP
#define CLPARSER_CLERRORS_HPP

/* ############# ERRORS ############# */

class NotEnoughArgumentsError : public std::exception {
private:
    string message {};

public:
    explicit NotEnoughArgumentsError(const string& msg) {this->message = "Not enough arguments on " + msg;}
    [[nodiscard]] const char * what() const noexcept override
    {
        return this->message.c_str();
    }
};

class PositionalArgumentRequiredError : public std::exception {
private:
    string message {};

public:
    explicit PositionalArgumentRequiredError(const string& msg) {this->message = msg + " option required!";}
    [[nodiscard]] const char * what() const noexcept override
    {
        return this->message.c_str();
    }
};

#endif //CLPARSER_CLERRORS_HPP
