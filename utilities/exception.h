#pragma once
#include <string>


class Exception {
private:
   std::string exceptionName;
public:
    Exception(std::string &exceptionName) : exceptionName(exceptionName) {}

    std::string getExceptionName() const { return this->exceptionName; }

};


class CantOpenFile : public Exception {
    CantOpenFile(std::string &exception) : Exception(exception) {}
};


