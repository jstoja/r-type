//
//  Exception.cpp
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#include "Exception.h"

Exception::Exception(std::string const& message, std::string const& type)
    : _type(type), _message(message) {
}

Exception::~Exception() throw() {
}

std::string const& Exception::getType() const {
    return _type;
}

std::string const& Exception::getMessage() const {
    return _message;
}

const char* Exception::what() const throw() {
    return std::string(getType() + ": " + _message).c_str();
}