#pragma once

#include <exception>
#include <sstream>
#include <string>

using namespace std;

class BomberException : public exception
{
private:
    std::string message;

public:
    BomberException(const std::string &msg) : message(msg) {}

    const char *what() const noexcept override
    {
        return message.c_str();
    }
};