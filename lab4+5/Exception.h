#pragma once

#include <exception>
#include <string>

class IOException : std::exception {
public:
    IOException() = default;

    explicit IOException(const std::string &file) {
        this->filename = file;
    }

    const char* what() const throw() override {
        std::string message = "Can't open file " + this->filename;
        return message.c_str();
    }

private:
    std::string filename;
};